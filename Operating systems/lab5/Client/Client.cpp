// Client.cpp: определяет точку входа для консольного приложения.
//

#include <conio.h>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;


struct message
{
	int sender; // номер процесса отправителя
	int receiver; // номер процесса получателя
	char text[10]; // текст сообщения
};



int main(int argc, char *argv[])
{
	int currentClientNumber = atoi(argv[1]);

	cout << "Client " << currentClientNumber << " is ready to work!" << endl;

	HANDLE hPipeToRead = (HANDLE)atoi(argv[2]);
	HANDLE hPipeToWrite = (HANDLE)atoi(argv[3]);
	HANDLE clientEvent = (HANDLE)atoi(argv[4]);

	DWORD dwBytesWritten;
	bool clientStoped = false;
	while (!clientStoped) {
		int command;
		cout << "\n\nChoose what to do?\n[1] - send message\n[2] - receive message\n[3] - end work" << endl;
		cin >> command;
		switch (command) {
		case 1: {
			message mes;
			mes.sender = currentClientNumber;
			cout << "Enter client number: ";
			cin >> mes.receiver;
			cout << "Enter message text: ";
			cin >> mes.text;
			if (WriteFile(hPipeToWrite, &mes, sizeof(mes), &dwBytesWritten, NULL)) {
				SetEvent(clientEvent);
				printf("Message sent.\n");
			} else
			{
				printf("Somthing went wrong.\n");
			}
			break;
		}
		case 2: {
			message mes;
			DWORD dwBytesRead;
			ReadFile(hPipeToRead, &mes, sizeof(mes), &dwBytesRead, NULL);
			printf("Client %d sent to you: %s \n", mes.sender, mes.text);
			break;
		}
		case 3: 
			clientStoped = true;
			break;
		}
	}
	ExitProcess(0);
}

