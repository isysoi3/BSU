#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <algorithm> 
#pragma warning(disable: 4996)

#define intsz sizeof(int)
#define SMALL_SPLITED_FILE_NAME ".tmp"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define SMALL_FILE_SIZE 100
int splited_files_count = 0;

void bubble_sort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
}

void split_input_file(const char* input) {
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
		int size = (i == small_file_count - 1 ? residue : SMALL_FILE_SIZE);
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
	}
	splited_files_count = small_file_count;

	std::cout << "Dividing finished\n";
	fin.close();
	free(name);
}

void merge_two_files_in_one(char* name1, char* name2, char* nameout) {
	std::fstream in1(name1, std::ios::binary);
	std::fstream in2(name2, std::ios::binary);
	std::ofstream out(nameout, std::ios::binary);
	int small_file_size1, small_file_size2;
	int number1, number2;

	in1 >> small_file_size1;
	in2 >> small_file_size2;
	in1 >> number1;
	in2 >> number2;


	int count = small_file_size1 + small_file_size2;
	out << count << "\n";

	int peek1 = small_file_size1 - 1;
	int peek2 = small_file_size2 - 1;
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

void merge_to_output_file(const char* output) {
	int merge = splited_files_count;
	char* name1 = new char[20];
	char* name2 = new char[20];
	char* nameout = new char[20];
	while (merge != 1) {
		for (int i = 0; i < merge / 2; ++i) {
			sprintf(name1, "%d%s", 2 * i, SMALL_SPLITED_FILE_NAME);
			sprintf(name2, "%d%s", 2 * i + 1, SMALL_SPLITED_FILE_NAME);
			sprintf(nameout, "m%d%s", i, SMALL_SPLITED_FILE_NAME);
			merge_two_files_in_one(name1, name2, nameout);
			remove(name1);
			remove(name2);
			sprintf(name1, "%d%s", i, SMALL_SPLITED_FILE_NAME);
			rename(nameout, name1);
		}
		if (merge % 2) {
			sprintf(name2, "%d%s", merge, SMALL_SPLITED_FILE_NAME);
			sprintf(nameout, "tail.tmp");
			merge_two_files_in_one(name1, name2, nameout);
			remove(name1);
			remove(name2);
			sprintf(name1, "%d%s", merge / 2, SMALL_SPLITED_FILE_NAME);
			rename(nameout, name1);
		}
		merge /= 2;
	}
	free(name1);
	free(name2);
	free(nameout);

	std::ifstream in("0.tmp", std::ios::binary);
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
	remove("0.tmp");
}

int main() {
	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	QueryPerformanceFrequency(&liFrequency);

	QueryPerformanceCounter(&liStartTime);
	split_input_file(INPUT_FILE);
	merge_to_output_file(OUTPUT_FILE);
	QueryPerformanceCounter(&liFinishTime);

	double dElapsedTime = (double(liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart) / 1000.0;
	printf("Elapsed time: %lf ms.\n", dElapsedTime);
}