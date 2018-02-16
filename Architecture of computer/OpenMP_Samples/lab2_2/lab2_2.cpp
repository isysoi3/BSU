// lab2_2.cpp: определяет точку входа для консольного приложения.
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
		double a = -3.54;
		double b = 2.41;
		long long n = 10000;
		double min_val = DBL_MAX, max_val = DBL_MIN;
		omp_set_nested(true);
		find_max_min(function, a, b, n, min_val, max_val);
		cout << "y(x) = sin(x) + cos(x) \nInterval: [" << a << ", " << b << "]\nMax value: "
			<< max_val << "\nMin value: " << min_val;
	}

private:
	static double function(double x)
	{
		return sin(x) + cos(x);
	}

	static void find_max_min(double(*function)(double), double a, double b, long long n, double &min_val, double &max_val)
	{
		double val;
#pragma omp parallel for private(val)
		for (int i = 0; i < n-1; ++i)
		{
			double x0 = a + (b - a)*i / n;
			double x1 = a + (b - a)*(i + 1) / n;
			val = (function(x1) - function(x0))/(x1-x0);

#pragma omp sections
			{
#pragma omp section 
			{
				if (val < min_val)
					min_val = val;
			}
#pragma omp section
			{
				if (val > max_val)
					max_val = val;
			}
			}
		}
	}
};



void main()
{
	Program::Main();
}


