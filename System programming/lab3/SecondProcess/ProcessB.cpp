#include <stdio.h>
#include <Windows.h>
#include <string>
#include <iostream>

int main()
{
	
	HANDLE namedPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\mypipe"), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, 1, sizeof(DWORD), sizeof(DWORD), 0, NULL);
	HANDLE eventA = CreateEvent(NULL, FALSE, FALSE, TEXT("AProcessWork"));
	HANDLE eventB = CreateEvent(NULL, FALSE, FALSE, TEXT("BProcessWork"));

	std::cout << "Process B\n";
	SetEvent(eventA);
	WaitForSingleObject(eventB, INFINITE);

	ConnectNamedPipe(namedPipe, NULL);
	
	LPVOID adress;
	DWORD dwBytesRead;
	//std::string* str;
	ReadFile(namedPipe, &adress, sizeof(adress), &dwBytesRead, static_cast<LPOVERLAPPED>(NULL));
	char* str = static_cast<char*>(adress);

	std::cout << str << "\n";

	SetEvent(eventA);
	WaitForSingleObject(eventB, INFINITE);

	CloseHandle(namedPipe);
	CloseHandle(eventA);
	CloseHandle(eventB);
	

	system("pause");
	return 0;
}
