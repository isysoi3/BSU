#define HAVE_STRUCT_TIMESPEC
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <chrono>
#include "pthread.h"
#include <algorithm> 

#define SMALL_SPLITED_FILE_NAME ".tmp"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define SMALL_FILE_SIZE 1000

std::queue<int> buffer;
pthread_mutex_t mutex;
pthread_cond_t cond_merge;

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

void *split(void *data) {
	char * input = (char*)data;
	std::ifstream fin(input);

	char* name = new char[20];
	int number;
	int big_file_size = 0;
	fin >> big_file_size;

	int small_file_count = big_file_size / SMALL_FILE_SIZE;
	int residue = big_file_size - small_file_count * SMALL_FILE_SIZE;
	if (residue)
		small_file_count += 1;

	for (int i = 0; i < small_file_count; ++i) {
		sprintf(name, "%d%s", i, SMALL_SPLITED_FILE_NAME);
		int size = ((i == small_file_count - 1 && residue != 0) ? residue : SMALL_FILE_SIZE);
		int* arr = new int[size];
		for (int i = 0; i < size; ++i) {
			fin >> number;
			arr[i] = number;
		}
		std::ofstream out(name);
		out << size << "\n";
		bubble_sort(arr, size);
		for (int j = 0; j < size; j++)
			out << arr[j] << " ";

		out.close();
	
		pthread_mutex_lock(&mutex);
		buffer.push(i);
		pthread_cond_signal(&cond_merge);
		pthread_mutex_unlock(&mutex);
	}

	do {
		pthread_mutex_lock(&mutex);
		pthread_cond_signal(&cond_merge);
		pthread_mutex_unlock(&mutex);
	} while(!buffer.empty());

	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&cond_merge);
	pthread_mutex_unlock(&mutex);
	
	delete name;
	pthread_exit(NULL);
}

void *merge(void *data) {
	char* output = (char*)data;
	char* name1 = new char[20];
	char* buf_name = new char[20];
	char* rez_name = new char[20];

	sprintf(rez_name, "rez.tmp");
	sprintf(buf_name, "buf.tmp");

	std::ofstream out(buf_name);
	out << 0;
	out.close();

	int file1;
	bool isFinished = false;

	while(!isFinished) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond_merge, &mutex);
		if(!buffer.empty()) {
			file1 = buffer.front();
			buffer.pop();
			sprintf(name1, "%d%s", file1, SMALL_SPLITED_FILE_NAME);
			merge_two_files_in_one(name1, buf_name, rez_name);
			remove(name1);
			remove(buf_name);
			rename(rez_name, buf_name);
		} else {
			isFinished = true;
		}
		pthread_mutex_unlock(&mutex);
	}

	remove(output);
	rename(buf_name, output);

	delete name1;
	delete buf_name;
	delete rez_name;

	pthread_exit(NULL);
}

//g++ -std=c++11 -pthread lab4.cpp -o lab4
int main() {
	pthread_attr_t attr;
	pthread_t sortThread, mergeThread;
	int sortThreadCreateResult, mergeThreadCreateResult;

   	pthread_attr_init(&attr);
   	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_merge, NULL);

	struct timespec startTime, finishTime;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);

	sortThreadCreateResult = pthread_create(&sortThread, &attr, split, (void*)INPUT_FILE);
	mergeThreadCreateResult = pthread_create(&mergeThread, &attr, merge, (void*)OUTPUT_FILE);
	pthread_join(sortThread, NULL);
	pthread_join(mergeThread, NULL);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finishTime);
	double resultTime = (finishTime.tv_sec + 1e-9*finishTime.tv_nsec)
                       - (startTime.tv_sec + 1e-9*startTime.tv_nsec);
	printf("Elapsed time: %.5f s.\n", resultTime);

	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_merge);

	return 0;
}