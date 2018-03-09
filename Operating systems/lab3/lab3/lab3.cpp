#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

CRITICAL_SECTION csArray;

struct params
{
	int n;
	int* mas;
	int index;
	HANDLE hBeginWorkEvent;
	HANDLE hStopWorkEvent;
	HANDLE* hContinueOrTerminateWork;
};

void resetElementsOfArrayWithThreadIndex(params* parameters) {
    EnterCriticalSection(&csArray);
    for (int i = 0; i < parameters->n; i++)
        if (parameters->mas[i] == (parameters->index + 1))
			parameters->mas[i] = 0;
    LeaveCriticalSection(&csArray);
}

bool isThreadTerminated(params* parameters) {
	return WaitForSingleObject(parameters->hContinueOrTerminateWork[1], 0) == WAIT_OBJECT_0;
}

void continueThreadWork(params* parameters) {
	ResetEvent(parameters->hContinueOrTerminateWork[0]);
}

DWORD WINAPI threadFunc(LPVOID param)
{
	params* parameters = (params*)param;
    int editsCount = 0;
    bool endWork = false;
    srand(parameters->index);

	WaitForSingleObject(parameters->hBeginWorkEvent, INFINITE);
	
	while (!endWork) {
		int random_index = rand() % parameters->n;
		EnterCriticalSection(&csArray);
		if (parameters->mas[random_index] == 0) {
			parameters->mas[random_index] = parameters->index + 1;
			LeaveCriticalSection(&csArray);
			editsCount++;
			Sleep(5);
		}
		else {
			cout << "\nThread " << parameters->index + 1 << " marked total " << editsCount << " elements, can`t mark element on " << random_index + 1 << " index\n";
			LeaveCriticalSection(&csArray);
			SetEvent(parameters->hStopWorkEvent);
			WaitForMultipleObjects(2, parameters->hContinueOrTerminateWork, FALSE, INFINITE);
            if (isThreadTerminated(parameters))
                endWork = true;
            else
				continueThreadWork(parameters);
		}
	}

    resetElementsOfArrayWithThreadIndex(parameters);

	return 0;
}

void printArray(int* mas, int n) {
	cout << "Array : \n";
	for (int i = 0; i < n; i++) {
		cout << mas[i] << " ";
	}
	cout << endl;
}

int main() {
	InitializeCriticalSection(&csArray);
	int n;
	cout << "Enter the size of array: ";
	cin >> n;
	int* mas = new int[n];

	for (int i = 0; i < n; i++) {
		mas[i] = 0;
	}

	int number_of_markers;
	cout << "Enter the number of markers : ";
	cin >> number_of_markers;

	HANDLE*	hThread = new HANDLE[number_of_markers];
	DWORD* IDThread = new DWORD[number_of_markers];
	params* parameters = new params[number_of_markers];
	HANDLE* hStopWorkEvents = new HANDLE[number_of_markers];
	HANDLE hBeginWorkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	bool* termenatedThreads = new bool[number_of_markers];

	for (int i = 0; i < number_of_markers; i++) {
		termenatedThreads[i] = false;
	}

	for (int i = 0; i < number_of_markers; i++) {
		parameters[i].hBeginWorkEvent = hBeginWorkEvent;
		parameters[i].hStopWorkEvent = hStopWorkEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		parameters[i].index = i;
		parameters[i].hContinueOrTerminateWork = new HANDLE[2];
		parameters[i].mas = mas;
		parameters[i].n = n;
		for (int j = 0; j < 2; j++) {
			parameters[i].hContinueOrTerminateWork[j] = CreateEvent(NULL, TRUE, FALSE, NULL);
		}
		hThread[i] = CreateThread(NULL, 0, threadFunc, (void* )&parameters[i], 0, &IDThread[i]);
	}

	SetEvent(hBeginWorkEvent);

	for (int i = 0; i < number_of_markers && i < n; i++) {
		WaitForMultipleObjects(number_of_markers, hStopWorkEvents, TRUE, INFINITE);
		printArray(mas, n);
		bool isThreadDeleted = false;
		while (!isThreadDeleted) {
			int threadIndexToTerminate;
			cout << "\nEnter the index of thread which you want to terminate(it starts from 1): ";
			cin >> threadIndexToTerminate;
			threadIndexToTerminate--;
			if (threadIndexToTerminate >= number_of_markers || threadIndexToTerminate < 0) {
				cout << "This thread isn`t exist";
				continue;
			}
			if (!termenatedThreads[threadIndexToTerminate]) {
				SetEvent(parameters[threadIndexToTerminate].hContinueOrTerminateWork[1]);
				WaitForSingleObject(hThread[threadIndexToTerminate], INFINITE);
				isThreadDeleted = true;
				termenatedThreads[threadIndexToTerminate] = true;
			}
			else
				cout << "This thread has already finished his work.";
		}
		printArray(mas, n);
		for (int i = 0; i < number_of_markers; i++) {
			if (!termenatedThreads[i]) {
				ResetEvent(parameters[i].hStopWorkEvent);
				SetEvent(parameters[i].hContinueOrTerminateWork[0]);
			}
		}
	}

	cout << "\nAll threads finished work\n";

	for (int i = 0; i < number_of_markers; i++)
		CloseHandle(hThread[i]);
	delete[] hThread;
	delete[] IDThread;
	delete[] mas;
	DeleteCriticalSection(&csArray);
	return 0;
}