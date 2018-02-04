#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
	HANDLE eventA = CreateEvent(NULL, FALSE, FALSE, TEXT("AProcessWork"));
	HANDLE eventB = CreateEvent(NULL, FALSE, FALSE, TEXT("BProcessWork"));
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	if (!CreateProcess(TEXT("SecondProcess.exe"), NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		std::cout << "CreateProcess failed";
		system("pause");
		return EXIT_FAILURE;
	}

	WaitForSingleObject(eventA, INFINITE);

	HANDLE namedPipe = CreateFile(TEXT("\\\\.\\pipe\\mypipe"),
		GENERIC_WRITE, FILE_SHARE_READ, static_cast<LPSECURITY_ATTRIBUTES>(NULL), OPEN_EXISTING, 0, NULL);

	std::cout << "Process A\n";
	std::string str;
	std::cout << "Enter a string\n";
	getline(std::cin, str);

	HANDLE hProcessB = pi.hProcess;
	//LPVOID AllocMem = VirtualAllocEx(hProcessB, NULL, sizeof(str), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	LPVOID AllocMem = VirtualAllocEx(hProcessB, NULL, str.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (AllocMem != NULL)
	{
		if (WriteProcessMemory(hProcessB, AllocMem, str.c_str(), str.size(), NULL))
		{
			DWORD dwBytesWritten;
			WriteFile(namedPipe, &AllocMem, sizeof(AllocMem), &dwBytesWritten, (LPOVERLAPPED)NULL);
		}
	}

	SetEvent(eventB);
	WaitForSingleObject(eventA, INFINITE);

	if (!VirtualFreeEx(hProcessB, AllocMem, 0, MEM_RELEASE))
	{
		std::cout << "VirtualFreeEx failed";
		system("pause");
		return EXIT_FAILURE;
	}

	CloseHandle(hProcessB);
	CloseHandle(namedPipe);
	CloseHandle(eventA);
	
	
	SetEvent(eventB);
	CloseHandle(eventB);

	return 0;
}
