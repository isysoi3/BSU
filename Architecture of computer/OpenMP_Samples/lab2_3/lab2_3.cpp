// lab2_3.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <omp.h>
#include <sstream>
using namespace std;

class Program
{
public:
	static void Main()
	{
		std::cout << "Function :  x * x + 1/x";
		double a = 1;
		double b = 2;
		std::cout << std::endl << "Interval: [" << a << ", " << b << "]" << std::endl;
		std::cout << solve(function, a, b, 1000);
	}

	static double function(double x)
	{
		return x * x + 1 / x;
	}

	static double solve(double(*func)(double), double a, double b, int n)
	{
		double sum = 0;
#pragma omp parallel for reduction(+:sum)
		for (int i = 0; i < n-1; i++) {
			double s = a + (b - a)*(i ) / n;
			double f = a + (b - a)*(i + 1) / n;
			sum += ((f - s) / 8) * (func(s) + 3 * func((2 * s +  f) / 3)
				+ 3 * func((s + 2 * f) / 3) + func(f));

		}

		return sum;
	}
};



void main()
{
	Program::Main();
}
