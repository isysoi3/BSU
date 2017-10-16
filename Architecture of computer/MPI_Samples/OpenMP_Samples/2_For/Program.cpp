#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(4);
		ForDefault();
		NewLine();
		ForOrdered();
		NewLine();
		ForChunk();
	}

private:
	static void ForDefault()
	{
		#pragma omp parallel for
		for (auto i = 0; i < 10; ++i)
		{
			auto threadNumber = omp_get_thread_num();

			auto buffer = std::stringstream();
			buffer << "Iteration i=" << i << " in thread " << threadNumber << std::endl;
			Print(buffer);
		}
	}

	static void ForOrdered()
	{
		#pragma omp parallel for ordered
		for (auto i = 0; i < 10; ++i)
		{
			auto threadNumber = omp_get_thread_num();

			auto buffer = std::stringstream();
			buffer << "Iteration i=" << i << " in thread " << threadNumber << std::endl;

			#pragma omp ordered
			Print(buffer);
		}
	}

	static void ForChunk()
	{
		const auto chunkSize = 1;
		#pragma omp parallel for schedule(static, chunkSize) ordered
		for (auto i = 0; i < 13; ++i)
		{
			auto threadNumber = omp_get_thread_num();

			auto buffer = std::stringstream();
			buffer << "Iteration i=" << i << " in thread " << threadNumber << std::endl;

			#pragma omp ordered
			Print(buffer);
		}
	}

	static void Print(const std::stringstream& buffer)
	{
		std::cout << buffer.str();
	}

	static void NewLine()
	{
		std::cout << std::endl;
	}
};

int main()
{
	Program::Main();
}