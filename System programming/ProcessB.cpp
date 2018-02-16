#include <stdio.h>
#include <Windows.h>
#include <string>
#include <iostream>

int main()
{
	HANDLE eventA = CreateEvent(NULL, FALSE, FALSE, TEXT("ProcessAWork"));
	HANDLE eventB = CreateEvent(NULL, FALSE, FALSE, TEXT("ProcessBWork"));
	HANDLE namedPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\mypipe"),
		PIPE_ACCESS_DUPLEX, // both server and client processes can read from and write to the pipe
		PIPE_TYPE_BYTE, // data is written to the pipe as a stream of bytes
		1, // the maximum number of instances that can be created for this pipe
		sizeof(DWORD), // the number of bytes to reserve for the output buffer
		sizeof(DWORD), // the number of bytes to reserve for the input buffer
		0, // a default time-out of 50 milliseconds
		NULL); // pipe gets a default security descriptor and the handle cannot be inherited

	std::cout << "Process B\n";
	SetEvent(eventA);
	WaitForSingleObject(eventB, INFINITE);// wait for string

	ConnectNamedPipe(namedPipe, NULL);
	// enables a named pipe server process to wait for a client process to connect to an instance 
	// of a named pipe

	LPVOID adress;
	DWORD dwBytesRead;
	std::string* str;
	// get the address
	ReadFile(namedPipe, &adress, sizeof(adress), &dwBytesRead, static_cast<LPOVERLAPPED>(NULL));
	str = static_cast<std::string*>(adress);

	std::cout << *str << "\n";
	system("pause");

	SetEvent(eventA);
	WaitForSingleObject(eventB, INFINITE);	// wait until process A free memory

	CloseHandle(eventA);
	CloseHandle(eventB);
	CloseHandle(namedPipe);

	return 0;
}
