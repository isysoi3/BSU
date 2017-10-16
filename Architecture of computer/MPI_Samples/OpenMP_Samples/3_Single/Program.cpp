#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(4);

		auto data = 123;

		#pragma omp parallel firstprivate(data)
		{
			ShowData(data);

			#pragma omp single copyprivate(data)
			{
				NewLine();
				Hi();
				ChangeData(data);
				NewLine();
			}

			ShowData(data);
		}
	}

private:
	static void ShowData(int data)
	{
		auto threadNumber = omp_get_thread_num();
		auto buffer = std::stringstream();
		buffer << "Data from thread " << threadNumber << " : " << data << std::endl;
		Print(buffer);
	}

	static void ChangeData(int& data)
	{
		auto threadNumber = omp_get_thread_num();
		data += 1000 * threadNumber;
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