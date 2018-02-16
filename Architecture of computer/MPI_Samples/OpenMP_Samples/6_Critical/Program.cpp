#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(100);

		NoCritical();
		Critical();
		Atomic();
	}

private:
	static void NoCritical()
	{
		auto count = 0;

		#pragma omp parallel
		{
			++count;
		}

		ShowCount(count);
	}

	static void Critical()
	{
		auto count = 0;

		#pragma omp parallel
		{
			#pragma omp critical
			++count;
		}

		ShowCount(count);
	}

	static void Atomic()
	{
		auto count = 0;

		#pragma omp parallel
		{
			// #pragma omp atomic update
			#pragma omp atomic
			++count;
		}

		ShowCount(count);
	}

	static void ShowCount(int count)
	{
		std::cout << "Count: " << count << std::endl;
	}
};

int main()
{
	Program::Main();
}