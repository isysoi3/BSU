#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>

using namespace std;

CRITICAL_SECTION cs;
volatile int n;
volatile int *mas;
HANDLE hBeginEvent;
HANDLE* hWorkEvent;
HANDLE** continueWorkingOrNot;


DWORD WINAPI threadFunc(LPVOID num)
{
	WaitForSingleObject(hBeginEvent, INFINITE);
	int threadIndex = (int)num;
	int editsCount = 0;
	bool endWork = false;
	srand(threadIndex);
	while (!endWork) {
		int random_index = rand() % n;
		EnterCriticalSection(&cs);
		if (mas[random_index] == 0) {
			LeaveCriticalSection(&cs);
			Sleep(5);
			EnterCriticalSection(&cs);
			mas[random_index] = threadIndex + 1;
			LeaveCriticalSection(&cs);
			editsCount++;
			Sleep(5);
		}
		else {
			cout << "\nThread on index " << threadIndex + 1 << " marked total " << editsCount << " elements, can`t mark element on " << random_index + 1 << " index\n";
			SetEvent(hWorkEvent[threadIndex]);
			LeaveCriticalSection(&cs);
			WaitForMultipleObjects(2, continueWorkingOrNot[threadIndex], FALSE, INFINITE);
			if (WaitForSingleObject(continueWorkingOrNot[threadIndex][1], 0) == WAIT_OBJECT_0)
				endWork = true;
			else
				ResetEvent(continueWorkingOrNot[threadIndex][0]);
		}
	}
	EnterCriticalSection(&cs);
	for (int i = 0; i < n; i++)
		if (mas[i] == (threadIndex + 1))
			mas[i] = 0;
	LeaveCriticalSection(&cs);
	return 0;
}

void initEvents(int size) {
	continueWorkingOrNot = new HANDLE*[size];
	hWorkEvent = new HANDLE[size];
	hBeginEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void closeEvents(int size) {
	CloseHandle(hBeginEvent);
	for (int i = 0; i < size; i++) {
		CloseHandle(hWorkEvent[i]);
		for (int j = 0; j < 2; j++) {
			CloseHandle(continueWorkingOrNot[i][j]);
		}
		delete[] continueWorkingOrNot[i];
	}

	delete[] hWorkEvent;
}

void printArray() {
	EnterCriticalSection(&cs);
	cout << "Array : \n";
	for (int i = 0; i < n; i++) {
		cout << mas[i] << " ";
	}
	cout << endl;
	LeaveCriticalSection(&cs);
}

int main() {
	InitializeCriticalSection(&cs);
	int k;
	cout << "Enter the size of array: ";
	cin >> k;
	n = k;
	mas = new int[n];

	for (int i = 0; i < n; i++) {
		mas[i] = 0;
	}

	int number_of_markers;
	cout << "Enter the number of markers : ";
	cin >> number_of_markers;

	initEvents(number_of_markers);
	HANDLE*	hThread = new HANDLE[number_of_markers];
	DWORD* IDThread = new DWORD[number_of_markers];

	for (int i = 0; i < number_of_markers; i++) {
		hThread[i] = CreateThread(NULL, 0, threadFunc, (void*)i, 0, &IDThread[i]);
		hWorkEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		continueWorkingOrNot[i] = new HANDLE[2];
		for (int j = 0; j < 2; j++) {
			continueWorkingOrNot[i][j] = CreateEvent(NULL, TRUE, FALSE, NULL);
		}
	}

	SetEvent(hBeginEvent);

	for (int i = 0; i < number_of_markers; i++) {
		WaitForMultipleObjects(n, hWorkEvent, TRUE, INFINITE);
		printArray();
		bool isThreadDeleted = false;
		while (!isThreadDeleted) {
			cout << "\nEnter the number of thread which you want to cancel: ";
			int threadNum;
			cin >> threadNum;
			threadNum--;
			if (threadNum >= number_of_markers) {
				cout << "This thread isn`t exist";
				continue;
			}
			if (WaitForSingleObject(hThread[threadNum], 0) != WAIT_OBJECT_0) {
				SetEvent(continueWorkingOrNot[threadNum][1]);
				WaitForSingleObject(hThread[threadNum], INFINITE);
				isThreadDeleted = true;
			}
			else
				cout << "This thread has already finished his work.";
		}
		printArray();
		for (int i = 0; i < number_of_markers; i++) {
			if (WaitForSingleObject(hThread[i], 0) != WAIT_OBJECT_0) {
				ResetEvent(hWorkEvent[i]);
				SetEvent(continueWorkingOrNot[i][0]);
			}
		}
	}

	cout << "All threads finished work\n";
	closeEvents(number_of_markers);
	for (int i = 0; i < number_of_markers; i++) {
		CloseHandle(hThread[i]);
	}

	delete[] hThread;
	delete[] IDThread;
	delete[] mas;
	DeleteCriticalSection(&cs);
	return 0;
}