// lab5.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;


struct message
{
	int sender; // номер процесса отправителя
	int receiver; // номер процесса получателя
	char text[10]; // текст сообщения
};


struct clients {
	PROCESS_INFORMATION* piCreators;
	STARTUPINFO* siCreators;

	HANDLE* hPipesRead;
	HANDLE* hPipesWrite;
	HANDLE* events;

	int amount;
};
int threadFunc(clients* c) {
	cout << "Press any key to stop the server" << endl;
	_getch();

	for (int i = 0; i < c->amount; i++) {
		CloseHandle(c->hPipesRead[i]);
		CloseHandle(c->hPipesWrite[i]);
		CloseHandle(c->events[i]);
		CloseHandle(c->piCreators[i].hThread);
		CloseHandle(c->piCreators[i].hProcess);
	}

	delete[] c->piCreators;
	delete[] c->siCreators;
	delete[] c->hPipesRead;
	delete[] c->hPipesWrite;
	delete[] c->events;

	ExitProcess(0);
}


int main()
{
	int numberOfClients;
	cout << "Enter the number of clients ";
	cin >> numberOfClients;

	//HANDLE endWork = CreateEvent(NULL, false, false, NULL);

	STARTUPINFO* siCreators = new STARTUPINFO[numberOfClients];
	PROCESS_INFORMATION* piCreators = new PROCESS_INFORMATION[numberOfClients];

	HANDLE* hPipesRead = new HANDLE[numberOfClients];
	HANDLE* hPipesWrite = new HANDLE[numberOfClients];

	HANDLE* events = new HANDLE[numberOfClients];

	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	for (int i = 0; i < numberOfClients; i++) {
		WCHAR params[100];

		events[i] = CreateEvent(&sa, false, false, NULL);
		ZeroMemory(&siCreators[i], sizeof(STARTUPINFO));
		CreatePipe(&hPipesRead[i], &hPipesWrite[i], &sa, 0);

		wsprintf(params, L"Client.exe %d %d %d %d",
			(int)(i + 1),
			(int)hPipesRead[i],
			(int)hPipesWrite[i],
			(int)events[i]);

		if (!CreateProcess(NULL, params, NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &siCreators[i], &piCreators[i])) {
			cout << "Can`t create client " << i + 1 << endl;
		}
	}

	HANDLE  hThread;
	DWORD IDThread;

	clients c = {
		piCreators,
		siCreators,
		hPipesRead,
		hPipesWrite,
		events,
		numberOfClients };

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFunc, (void*)&c, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();

	while (true) {
		int idEvent = WaitForMultipleObjects(numberOfClients, events, false, INFINITE);
		//idEvent -= WAIT_OBJECT_0;
		message mes;
		DWORD dwBytesRead;

		if (!ReadFile(hPipesRead[idEvent], &mes, sizeof(mes) , &dwBytesRead, NULL)) {
			printf("Read from pipe failed.\n");
			printf("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		const int receiver = mes.receiver - 1;
		if (receiver >= 0 && receiver < numberOfClients) {
			DWORD dwBytesWritten;
			if (!WriteFile(hPipesWrite[receiver], &mes, sizeof(mes), &dwBytesWritten, NULL))
			{
				printf("Write to pipe failed.\n");
				printf("Press any key to finish.\n");
				_getch();
				return GetLastError();
			}
		} else
		{
			printf("Sender %d: receiver %d doesn`t exist.\n", mes.sender, receiver + 1);
		}
	}
}

