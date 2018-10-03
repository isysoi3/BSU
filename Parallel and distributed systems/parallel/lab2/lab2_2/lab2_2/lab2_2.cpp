// lab2_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;
int** matrix;
int* b_vect;
int* result_vect;
int n;
struct matrix_rows {
	int start;
	int step;
	int count;
};
DWORD WINAPI thread_func(LPVOID param) {
	matrix_rows* mr = (matrix_rows*)param;
	for (int i = 0; i < mr->count; ++i) {
		int index = mr->start + i * mr->step;
		for (int j = 0; j < n; ++j)
			result_vect[index] += matrix[index][j] * b_vect[j];
	}
	return 0;
}

int main() {
	cout << "Enter matrix size: ";
	cin >> n;
	matrix = new int*[n];
	b_vect = new int[n];
	result_vect = new int[n];
	for (int i = 0; i < n; ++i) {
		b_vect[i] = rand();
		matrix[i] = new int[n];
		for (int j = 0; j < n; ++j)
			matrix[i][j] = rand();
	}
	int type;
	while (true) {
		cout << "\n\nEnter type:\n1 - consecutive\n2 - continuous\n3 - cyclic\n\tany button - exit\n";
		cin.clear();
		cin >> type;
		for (int i = 0; i < n; ++i)
			result_vect[i] = 0;
		LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
		QueryPerformanceFrequency(&liFrequency);

		if (type == 1) {
			QueryPerformanceCounter(&liStartTime);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j)
					result_vect[i] += matrix[i][j] * b_vect[j];
			}
			QueryPerformanceCounter(&liFinishTime);
			double dElapsedTime = 1000.*(liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
			cout << "Elapsed time: " << dElapsedTime;
		}
		else if (type == 2 || type == 3) {
			int thread_count;
			cout << "Enter number of threads: ";
			cin >> thread_count;
			HANDLE* hThread = new HANDLE[thread_count];
			matrix_rows* param = new matrix_rows[thread_count];
			QueryPerformanceCounter(&liStartTime);
			if (type == 2)
				for (int i = 0; i < thread_count; ++i) {
					param[i].step = 1;
					param[i].count = n / thread_count + ((i < (n % thread_count)) ? 1 : 0);
					param[i].start = (i == 0 ? 0 : (param[i - 1].start + param[i - 1].count));
				}
			else
				for (int i = 0; i < thread_count; ++i) {
					param[i].step = thread_count;
					param[i].count = n / thread_count + ((i < (n % thread_count)) ? 1 : 0);
					param[i].start = i;
				}

			for (int i = 0; i < thread_count; ++i)
				hThread[i] = CreateThread(NULL, 0, thread_func, (LPVOID)(param + i), 0, NULL);
			WaitForMultipleObjects(thread_count, hThread, TRUE, INFINITE);
			for (int i = 0; i < thread_count; ++i)
				CloseHandle(hThread[i]);
			delete[] hThread;
			delete[] param;
			QueryPerformanceCounter(&liFinishTime);
			double dElapsedTime = 1000.*(liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
			cout << "Time: " << dElapsedTime;

		}
		else
			break;
	}
	for (int i = 0; i < n; ++i)
		delete[] matrix[i];
	delete matrix;
	delete[] b_vect;
	delete[] result_vect;
}

