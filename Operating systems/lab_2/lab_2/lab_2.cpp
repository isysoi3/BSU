// lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;

struct myPair {
	int* matrix_row;
	int* vector;
	int* result;
	int n;
	int index;
};

DWORD WINAPI Add(LPVOID iNum)
{
	int rez = 0;
	for (int i = 0; i < ((myPair*)iNum)->n; i++) {
		rez += ((myPair*)iNum)->matrix_row[i] * ((myPair*)iNum)->vector[i];
		Sleep( (((myPair*)iNum)->n - ((myPair*)iNum)->index) * 300);
	}
	((myPair*)iNum)->result[((myPair*)iNum)->index] = rez;
	printf("произведение строки %i на вектор равно : %i\n", ((myPair*)iNum)->index, rez);
	return 0;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Размерность квадратной матрицы и вектора" << endl;
	cin >> n;
	int **matrix = new int*[n];
	int *vector = new int[n];
	HANDLE*  hThreadMulArray = new HANDLE[n];
	int *result = new int[n];
	myPair ** myPairArray = new myPair*[n];

	cout << "Введите матрицу\n";
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}

	cout << "Введите вектор\n";
	for (int i = 0; i < n; i++) {
		cin >> vector[i];
	}

	cout << endl;

	for (int i = 0; i < n; i++) {
		DWORD	IDThreadMul;
		myPairArray[i] = new myPair();
		myPairArray[i]->n = n;
		myPairArray[i]->result = result;
		myPairArray[i]->matrix_row = matrix[i];
		myPairArray[i]->vector = vector;
		myPairArray[i]->index = i;
		hThreadMulArray[i] = CreateThread(NULL, 0, Add, (void*)myPairArray[i], 0, &IDThreadMul);
	}

	WaitForMultipleObjects(n, hThreadMulArray, TRUE, INFINITE);

	cout << endl << "Результирующий вектор" << endl;
	for (int i = 0; i < n; i++) {
		cout << result[i] << " ";
	}


	delete[] result;
	delete[] vector;
	for (int i = 0; i < n; i++) {
		CloseHandle(hThreadMulArray[i]);
		delete[] matrix[i];
		delete myPairArray[i];
	}
	delete[] hThreadMulArray;

	return 0;
}
