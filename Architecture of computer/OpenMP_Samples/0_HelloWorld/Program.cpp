#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(4);

		#pragma omp parallel
		{
			Hi();
			if (IsMaster())
			{
				ShowThreadsCount();
			}
		}
	}

private:
	static void Hi()
	{
		auto threadNumber = omp_get_thread_num();
		auto buffer = std::stringstream();
		buffer << "Hi from thread " << threadNumber << std::endl;
		Print(buffer);
	}

	static bool IsMaster()
	{
		auto threadNumber = omp_get_thread_num();
		return (threadNumber == 0);
	}

	static void ShowThreadsCount()
	{
		auto buffer = std::stringstream();
		auto threadsCount = omp_get_num_threads();
		buffer << "Number of threads " << threadsCount << std::endl;
		Print(buffer);
	}

	static void Print(const std::stringstream& buffer)
	{
		std::cout << buffer.str();
	}
};

int main()
{
	Program::Main();
}