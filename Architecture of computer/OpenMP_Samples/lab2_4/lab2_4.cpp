// lab2_4.cpp: определяет точку входа для консольного приложения.
//

#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;
class Program
{
public:
	static void Main()
	{
		int n = 2;
		omp_set_num_threads(3);
		double **matrix = new double *[n];
		double *b = new double[n];
		double *rez = new double[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			b[i] = rand() / 100;
			matrix[i] = new double[n];
		}
		randomiseMatrix(matrix, n, n);
		

		cout << "Matrix : " << endl;
		Print(matrix, n, n);
		cout << std::endl << "Column of free members: " << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << b[i] << " ";
		std::cout << std::endl;

		Gauss(matrix, b, rez, n);

		std::cout << "Result: " << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << rez[i] << " ";

		for (int a = 0; a < n; a++)
			delete[] matrix[a];
		delete[] b;
		delete[] rez;

	}

private:
	static void randomiseMatrix(double** matrix, int m, int n)
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = rand() / 100;
			}
		}
	}

	static void Print(double** matrix, int m, int k)
	{
		for (int a = 0; a < m; a++, cout << endl)
			for (int b = 0; b < k; b++)
				cout << matrix[a][b] << " ";
	}

	static void Gauss(double **a, double *b, double *rez, int n) {
#pragma omp parallel  for ordered
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int t = i + 1; t < n; t++) {
					a[j][t] = (a[j][t] * a[i][i] / a[j][i]) - a[i][t];
				}
				b[j] = (b[j] * a[i][i] / a[j][i]) - b[i];
				a[j][i] = 0;
			}
		}

		for (int i = n - 1; i >= 0; i--) {
			rez[i] = b[i];
			for (int j = i + 1; j < n; j++) {
				rez[i] -= a[i][j] * rez[j];
			}
			rez[i] /= a[i][i];
		}

	}

};

int main()
{
	Program::Main();
}

