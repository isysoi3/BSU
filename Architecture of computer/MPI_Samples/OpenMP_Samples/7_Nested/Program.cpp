#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		omp_set_nested(false);
		ShowNestedStatus();
		DoParallel();

		NewLine();

		omp_set_nested(true);
		ShowNestedStatus();
		DoParallel();
	}

private:
	static void DoParallel()
	{
		#pragma omp parallel num_threads(3)
		{
			PrintText("Hi!");
						
			#pragma omp parallel num_threads(2)
			{
				PrintText("  Hi!");
				PrintText("  Bye!");;
			}

			PrintText("Bye!");
		}
	}

	static void ShowNestedStatus()
	{
		auto nestedAllowed = omp_get_nested() ? "true" : "false";
		std::cout << "Nested allowed: " << nestedAllowed << std::endl;
	}

	static void PrintText(const char* s)
	{
		auto threadNumber = omp_get_thread_num();
		auto buffer = std::stringstream();
		buffer << s << " (thread " << threadNumber << ")" << std::endl;
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