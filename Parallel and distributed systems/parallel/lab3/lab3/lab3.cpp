#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#pragma warning(disable: 4996)

int small_file_size_default = (1 << 15);
#define intsz sizeof(int)
#define splited_file_name ".tmp"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void sort(int* arr, int n) {
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				int buf = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buf;
			}
}

int split(const char* input) {
	std::ifstream fin(input);

	int big_file_size = 0;
	fin >> big_file_size;

	int small_file_count = big_file_size / small_file_size_default;
	char* name = new char[20];
	int number;
	for (int i = 0; i < small_file_count; ++i) {
		sprintf(name, "%d%s", i, splited_file_name);
		int* arr = new int[small_file_size_default];
		for (int i = 0; i < small_file_size_default; ++i) {
			fin >> number;
			arr[i] = number;
		}
		std::ofstream out(name);
		out << small_file_size_default << "\n";
		sort(arr, small_file_size_default);
		for (int j = 0; j < small_file_size_default; j++) {
			out << arr[j] << " ";
		}
		out.close();
	}
	int count = (big_file_size % small_file_size_default);
	if (count) {
		sprintf(name, "%d%s", small_file_count, splited_file_name);
		int* arr = new int[count];
		for (int i = 0; i < count; ++i) {
			fin >> number;
			arr[i] = number;
		}
		std::ofstream out(name);
		out << count << '\n';
		sort(arr, count);
		for (int j = 0; j < count; j++) {
			out << arr[j] << " ";
		}
		out.close();
	}

	fin.close();
	std::cout << "Dividing finished\n";
	free(name);
	if (count)
		return small_file_count + 1;
	return small_file_count;
}

void merge_files(char* name1, char* name2, char* nameout) {
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

void merge(int small_file_count) {
	int merge = small_file_count;
	char* name1 = new char[20];
	char* name2 = new char[20];
	char* nameout = new char[20];
	while (merge != 1) {
		for (int i = 0; i < merge / 2; ++i) {
			sprintf(name1, "%d.tmp", 2 * i);
			sprintf(name2, "%d.tmp", 2 * i + 1);
			sprintf(nameout, "m%d.tmp", i);
			merge_files(name1, name2, nameout);
			remove(name1);
			remove(name2);
			sprintf(name1, "%d.tmp", i);
			rename(nameout, name1);
		}
		if (merge % 2) {
			sprintf(name1, "%d.tmp", merge / 2);
			sprintf(name2, "%d.tmp", merge);
			sprintf(nameout, "tail.tmp");
			merge_files(name1, name2, nameout);
			remove(name1);
			remove(name2);
			sprintf(name1, "%d.tmp", merge / 2);
			rename(nameout, name1);
		}
		merge /= 2;
	}
	free(name1);
	free(name2);
	free(nameout);
}

void to_nornal_txt(const char* output) {
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
	int start = clock();

	int splited_files_count = split(INPUT_FILE);
	merge(splited_files_count);
	to_nornal_txt(OUTPUT_FILE);

	start = clock() - start;
	printf("Elapsed time: %d ms.\n", start);
}