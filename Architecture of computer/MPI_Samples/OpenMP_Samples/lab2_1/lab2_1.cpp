// lab2_1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <omp.h>
#include <sstream>
#include <ctime>


using namespace std;

class Program
{
public:

	static void Main()
	{
		srand(time(NULL));
		int k = 5, m = 2, n = 3;

		int **matrix1 = new int*[m];
		int **matrix2 = new int*[n];
		int **result = new int*[m];

		for (int i = 0; i < m; i++)
			matrix1[i] = new int[n];
		for (int i = 0; i < n; i++)
			matrix2[i] = new int[k];

		for (int i = 0; i < m; i++)
			result[i] = new int[k];

		randomiseMatrix(matrix1, m, n);
		randomiseMatrix(matrix2, n, k);


		int threadsNum = 2;
		omp_set_num_threads(threadsNum);
		int i, j, h;
#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, h)
		for (i = 0; i < m; i++) {
			for (j = 0; j < k; j++) {
				result[i][j] = 0;
				for (h = 0; h < n; h++) {
					result[i][j] += matrix1[i][h] * matrix2[h][j];
				}
			}
		}

		cout << endl << "First matrix: " << endl;
		Print(matrix1, m, n);
		cout << endl << "Second matrix: " << endl;
		Print(matrix2, n, k);
		cout << endl << "Result: " << endl;
		Print(result, m, k);

		for (int a = 0; a < m; a++)
			delete[]matrix1[a];
		for (int a = 0; a < n; a++)
			delete[]matrix2[a];

		for (int a = 0; a < m; a++)
			delete[]result[a];
	}

private:

	static void randomiseMatrix(int** matrix, int m, int n)
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = rand() % 11;
			}
		}
	}

	static bool IsMaster()
	{
		auto threadNumber = omp_get_thread_num();
		return (threadNumber == 0);
	}

	static void Print(int** matrix, int m, int k)
	{
		for (int a = 0; a < m; a++, cout << endl)
			for (int b = 0; b < k; b++)
				cout << matrix[a][b] << " ";
	}

};



void main()
{
	Program::Main();
}

