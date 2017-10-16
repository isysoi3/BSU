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
		double max_val = -10;
		double min_val = 10;
		int threadsNum = 2;
		omp_set_num_threads(threadsNum);
		double wall_timer = omp_get_wtime();
		find_max_min(function, 0, 0.31415, 100000, min_val, max_val);
		cout << "y(x) = sin(x) + cos (x) | (0, Pi)\nMax value: " << max_val << "\nMin value: " << min_val << "\nWorktime: " << omp_get_wtime() - wall_timer;
	}

private:
	static double function(double x)
	{
		return sin(x) + cos(x);
	}

	static void find_max_min(double(*function)(double), double a, double b, long long NODECNT, double &min_val, double &max_val)
	{
#pragma omp parallel for
		for (int i = 0; i < NODECNT; ++i)
		{
			double val = function(a + (b - a)*i / NODECNT);
#pragma section reduction(min:min_val)
			{
				if (val < min_val)
					min_val = val;
			}
#pragma section reduction(max:max_val)
			{
				if (val > max_val)
					max_val = val;
			}
		}
	}
};



void main()
{
	Program::Main();
}


