#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(4);
		ProcessDefault();
		NewLine();
		ProcessShared();
		NewLine();
		ProcessPrivate();
		NewLine();
		ProcessFirstPrivate();
	}

private:
	static void ProcessDefault()
	{
		auto data = 123;

		#pragma omp parallel
		{
			auto threadNumber = omp_get_thread_num();
			data += threadNumber;

			auto buffer = std::stringstream();
			buffer << "Data in thread " << threadNumber << " = " << data << std::endl;
			Print(buffer);
		}

		std::cout << "Default data: " << data << std::endl;
	}

	static void ProcessShared()
	{
		auto data = 123;

		#pragma omp parallel shared(data)
		{
			auto threadNumber = omp_get_thread_num();
			data += threadNumber;

			auto buffer = std::stringstream();
			buffer << "Data in thread " << threadNumber << " = " << data << std::endl;
			Print(buffer);
		}

		std::cout << "Shared data: " << data << std::endl;
	}

	static void ProcessPrivate()
	{
		auto data = 123;

		#pragma omp parallel private(data)
		{
			data = 0;
			auto threadNumber = omp_get_thread_num();
			data += threadNumber;

			auto buffer = std::stringstream();
			buffer << "Data in thread " << threadNumber << " = " << data << std::endl;
			Print(buffer);
		}

		std::cout << "Private data: " << data << std::endl;
	}

	static void ProcessFirstPrivate()
	{
		auto data = 123;

		#pragma omp parallel firstprivate(data)
		{
			auto threadNumber = omp_get_thread_num();
			data += threadNumber;

			auto buffer = std::stringstream();
			buffer << "Data in thread " << threadNumber << " = " << data << std::endl;
			Print(buffer);
		}

		std::cout << "First private data: " << data << std::endl;
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