// delegation.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Windows.h"
#include <fstream>
#include <iostream>
#include <queue>
#pragma warning(disable: 4996)

#define threads_num 2

#define intsz sizeof(int)
#define SMALL_SPLITED_FILE_NAME ".tmp"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define SMALL_FILE_SIZE 100

//command 0 - exit thread
//command 1 - sort + out to file
struct thread_command {
	int command;
	int * arr;
	int arrSize;
	int outFile;
	int in1File;
	int in2File;
};


thread_command * commands_to_threads;

HANDLE* hThreads;
HANDLE* eventStartWork;
HANDLE* eventFinishWork;

HANDLE eventHasFilesToMerge;
CRITICAL_SECTION cs_queue;
std::queue <int> mergQue;

void bubble_sort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
}

void merge_two_files_in_one(char* name1, char* name2, char* nameout) {
	std::fstream in1(name1);
	std::fstream in2(name2);
	std::ofstream out(nameout);
	int file1_size, file2_size;
	int number1, number2;
	in1 >> file1_size;
	in2 >> file2_size;
	in1 >> number1;
	in2 >> number2;
	int count = file1_size + file2_size;
	out << count << "\n";
	int peek1 = file1_size;
	int peek2 = file2_size;
	for (int i = 0; i < count; ++i) {
		if (!peek1) {
			out << number2 << " ";
			in2 >> number2;
			continue;
		}
		if (!peek2) {
			out << number1 << " ";
			in1 >> number1;
			continue;
		}
		if (number1 > number2) {
			out << number2 << " ";
			in2 >> number2;
			peek2--;
		}
		else {
			out << number1 << " ";
			in1 >> number1;
			peek1--;
		}
	}
	in1.close();
	in2.close();
	out.close();
}

void create_output_file(char* output, char * name) {
	std::ifstream in(name);
	std::ofstream out(output);
	int count;
	in >> count;
	int number;
	out << count << '\n';
	for (int i = 0; i < count; ++i) {
		in >> number;
		out << number << " ";
	}
	out.close();
	in.close();
}

DWORD WINAPI thread_fnc(LPVOID data) {
	int thread_num = (int)data;
	while (true) {
		WaitForSingleObject(eventStartWork[thread_num], INFINITE);
		if (!commands_to_threads[thread_num].command) {
			break;
		}
		if (commands_to_threads[thread_num].command == 1) {
			char name[20];
			bubble_sort(commands_to_threads[thread_num].arr, commands_to_threads[thread_num].arrSize);
			sprintf(name, "%d.tmp", commands_to_threads[thread_num].outFile);
			std::ofstream out(name);
			out << commands_to_threads[thread_num].arrSize << "\n";
			for (int j = 0; j < commands_to_threads[thread_num].arrSize; j++) {
				out << commands_to_threads[thread_num].arr[j] << " ";
			}
			out.close();
			free(commands_to_threads[thread_num].arr);
		}
		else if (commands_to_threads[thread_num].command == 2) {
			//printf("Merge %d and %d -> %d\n", 
			//commands_to_threads[thread_num].in1File, commands_to_threads[thread_num].in2File,
			//commands_to_threads[thread_num].outFile);
			char name1[20];
			char name2[20];
			char nameout[20];
			sprintf(name1, "%d.tmp", commands_to_threads[thread_num].in1File);
			sprintf(name2, "%d.tmp", commands_to_threads[thread_num].in2File);
			sprintf(nameout, "%d.tmp", commands_to_threads[thread_num].outFile);
			merge_two_files_in_one(name1, name2, nameout);
		}
		EnterCriticalSection(&cs_queue);
		mergQue.push(commands_to_threads[thread_num].outFile);
		LeaveCriticalSection(&cs_queue);
		SetEvent(eventHasFilesToMerge);
		SetEvent(eventFinishWork[thread_num]);
	}
	return 0;
}

void generatePair(thread_command* command) {
	EnterCriticalSection(&cs_queue);
	if (!mergQue.empty()) {
		command->in1File = mergQue.front();
		mergQue.pop();
		if (!mergQue.empty()) {
			command->in2File = mergQue.front();
			mergQue.pop();
			if (mergQue.empty()) {
				ResetEvent(eventHasFilesToMerge);
			}
			LeaveCriticalSection(&cs_queue);
			return;
		}
		ResetEvent(eventHasFilesToMerge);
		LeaveCriticalSection(&cs_queue);
		WaitForSingleObject(eventHasFilesToMerge, INFINITE);
		EnterCriticalSection(&cs_queue);
		command->in2File = mergQue.front();
		mergQue.pop();
		LeaveCriticalSection(&cs_queue);
		return;
	}
	LeaveCriticalSection(&cs_queue);
	WaitForSingleObject(eventHasFilesToMerge, INFINITE);
	EnterCriticalSection(&cs_queue);
	command->in1File = mergQue.front();
	mergQue.pop();
	LeaveCriticalSection(&cs_queue);

	WaitForSingleObject(eventHasFilesToMerge, INFINITE);
	EnterCriticalSection(&cs_queue);
	command->in2File = mergQue.front();
	mergQue.pop();
	LeaveCriticalSection(&cs_queue);
}

int main() {
	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	// �������� �������
	QueryPerformanceFrequency(&liFrequency);
	// �������� ��������� �����  
	QueryPerformanceCounter(&liStartTime);
	InitializeCriticalSection(&cs_queue);

	commands_to_threads = new thread_command[threads_num];
	eventStartWork = new HANDLE[threads_num];
	eventFinishWork = new HANDLE[threads_num];
	hThreads = new HANDLE[threads_num];
	eventHasFilesToMerge = CreateEvent(NULL, FALSE, FALSE, NULL);

	for (int i = 0; i < threads_num; i++) {
		eventStartWork[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		eventFinishWork[i] = CreateEvent(NULL, FALSE, TRUE, NULL);
		hThreads[i] = CreateThread(NULL, NULL, thread_fnc, (void*)i, NULL, NULL);
	}

	//give first task foreach threads
	//first task is sort array and print it in output file
	std::ifstream in("input.txt");
	int array_size;
	in >> array_size;
	int files_number = (array_size + SMALL_FILE_SIZE - 1) / SMALL_FILE_SIZE;
	int current_number;
	for (int i = 0; i < files_number; i++) {
		int current_array_size;
		if (array_size - (i)*SMALL_FILE_SIZE > SMALL_FILE_SIZE) {
			current_array_size = SMALL_FILE_SIZE;
		}
		else {
			current_array_size = array_size - (i)*SMALL_FILE_SIZE;
		}
		int* arr = new int[current_array_size];
		for (int j = 0; j < current_array_size; j++) {
			in >> current_number;
			arr[j] = current_number;
		}
		int freeThread = WaitForMultipleObjects(threads_num, eventFinishWork, FALSE, INFINITE) - WAIT_OBJECT_0;
		commands_to_threads[freeThread].arr = arr;
		commands_to_threads[freeThread].arrSize = current_array_size;
		commands_to_threads[freeThread].command = 1;
		commands_to_threads[freeThread].outFile = i;
		SetEvent(eventStartWork[freeThread]);
	}
	in.close();

	int fileNum = files_number;
	//give second work foreach threads
	//merge files
	while (files_number != 1) {
		for (int i = 0; i < files_number / 2 + files_number % 2; i++) {
			int freeThread = WaitForMultipleObjects(threads_num, eventFinishWork, FALSE, INFINITE) - WAIT_OBJECT_0;
			generatePair(&commands_to_threads[freeThread]);
			commands_to_threads[freeThread].outFile = fileNum++;
			commands_to_threads[freeThread].command = 2;
			SetEvent(eventStartWork[freeThread]);
		}
		files_number /= 2;
	}

	//kill all threads
	for (int i = 0; i < threads_num; ++i) {
		int freeThread = WaitForMultipleObjects(threads_num, eventFinishWork, FALSE, INFINITE) - WAIT_OBJECT_0;
		commands_to_threads[freeThread].command = 0;
		SetEvent(eventStartWork[freeThread]);
	}

	char name[20];
	sprintf(name, "%d.tmp", (fileNum - 1));
	create_output_file((char*)"output.txt", name);

	for (int i = 0; i < fileNum; i++) {
		char name[20];
		sprintf(name, "%d.tmp", i);
		remove(name);
	}

	//close handles
	WaitForMultipleObjects(threads_num, hThreads, TRUE, INFINITE);
	QueryPerformanceCounter(&liFinishTime);

	double dElapsedTime = (double(liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart);
	printf("Elapsed time: %lf s.\n", dElapsedTime);

	for (int i = 0; i < threads_num; ++i) {
		CloseHandle(eventStartWork[i]);
		CloseHandle(eventFinishWork[i]);
		CloseHandle(hThreads[i]);
	}

	DeleteCriticalSection(&cs_queue);
	CloseHandle(eventHasFilesToMerge);
	delete[] hThreads;
	delete[] eventFinishWork;
	delete[] eventStartWork;

	return 0;
}
