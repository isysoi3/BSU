#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(4);

		Master();
		NewLine();
		Barrier();
	}

private:
	static void Master()
	{
		auto data = 123;

		#pragma omp parallel shared(data)
		{
			ShowData(data);

			#pragma omp master
			{
				Hi();
				ChangeData(data);
			}

			ShowData(data);
		}
	}

	static void Barrier()
	{
		auto data = 123;

		#pragma omp parallel shared(data)
		{
			ShowData(data);

			#pragma omp barrier

			#pragma omp master
			{
				Hi();
				ChangeData(data);
			}

			#pragma omp barrier

			ShowData(data);
		}
	}

	static void ShowData(int data)
	{
		auto threadNumber = omp_get_thread_num();
		auto buffer = std::stringstream();
		buffer << "Data from thread " << threadNumber << " : " << data << std::endl;
		Print(buffer);
	}

	static void ChangeData(int& data)
	{
		data += 1000;
	}

	static void Hi()
	{
		auto threadNumber = omp_get_thread_num();
		auto buffer = std::stringstream();
		buffer << "Hi from thread " << threadNumber << std::endl;
		Print(buffer);
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