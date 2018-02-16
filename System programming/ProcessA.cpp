#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>

int main()
{

	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	//creating 2 events for syncronization
	HANDLE eventA = CreateEvent(NULL, // cannot be inherited by child processes
		FALSE, // state of an event object remains signaled (any number of waiting threads, or threads that subsequently specify the same 
			  // event object in one of the wait functions, can be released) until it is reset to nonsignaled by the ResetEvent function
		FALSE, // the initial state of the event object is nonsignaled
		"ProcessAWork");
	HANDLE eventB = CreateEvent(NULL, FALSE, FALSE, TEXT("ProcessBWork"));
	
	if (!CreateProcess(TEXT("SecondProcess.exe"), NULL,
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		std::cout << "CreateProcess failed";
		system("pause");
		return EXIT_FAILURE;
	}
	HANDLE hProcessB = pi.hProcess;

	WaitForSingleObject(eventA, INFINITE); // wait until process B create pip

	HANDLE namedPipe = CreateFile(TEXT("\\\\.\\pipe\\mypipe"),
		GENERIC_WRITE, // write access
		FILE_SHARE_READ, // enables open operations to request delete access
		static_cast<LPSECURITY_ATTRIBUTES>(NULL), // cannot be inherited by child processes 
		OPEN_EXISTING, // open only if it exists
		0,
		NULL); // when opening an existing file, CreateFile ignores this parameter

	std::cout << "Process A\n";
	std::string data;
	std::cout << "Enter a string\n";
	getline(std::cin, data);
	std::cout << sizeof(std::string) << ":" << sizeof(data);

	LPVOID AllocMem = VirtualAllocEx(hProcessB,
		NULL, // the function determines where to allocate the region
		std::strlen(data.c_str()) * sizeof(std::string),
		MEM_COMMIT | MEM_RESERVE, // reserve and commit pages in one step
		PAGE_EXECUTE_READWRITE); // read-only or read/write access to the committed region of pages

	if (AllocMem != NULL)
	{
		if (WriteProcessMemory(hProcessB, AllocMem, &data, std::strlen(data.c_str()) * sizeof(std::string), NULL))
		{
			DWORD dwBytesWritten;
			WriteFile(namedPipe, &AllocMem, sizeof(AllocMem), &dwBytesWritten, (LPOVERLAPPED)NULL);
			// send the address
		}
	}

	// allow process B to act
	SetEvent(eventB);
	WaitForSingleObject(eventA, INFINITE);


	if (!VirtualFreeEx(hProcessB, AllocMem, 0, MEM_RELEASE))
	{
		std::cout << "VirtualFreeEx failed";
		system("pause");
		return EXIT_FAILURE;
	}

	CloseHandle(eventA);
	CloseHandle(namedPipe);
	CloseHandle(hProcessB);
	SetEvent(eventB);
	CloseHandle(eventB);

	return 0;
}
