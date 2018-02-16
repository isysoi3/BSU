#include <omp.h>
#include <iostream>
#include <sstream>
#include <windows.h>

class Program
{
public:
	static void Main()
	{
		auto data = 123;

		#pragma omp parallel num_threads(4)
		{
			ShowText("Hi!");

			#pragma omp sections lastprivate(data) nowait
			{
				#pragma omp section
				{
					ShowText("  Start section 1");
					Sleep(1000);
					ChangeData(data);
					ShowText("    Finish section 1");
				}

				#pragma omp section
				{
					ShowText("  Start section 2");
					Sleep(2000);
					ChangeData(data);
					ShowText("    Finish section 2");
				}

				#pragma omp section
				{
					ShowText("  Start section 3");
					Sleep(3000);
					ChangeData(data);
					ShowText("    Finish section 3");
				}
			}

			ShowText("      Bye!");
		}

		ShowData(data);
	}

private:
	static void ShowText(const char* s)
	{
		auto threadNumber = omp_get_thread_num();
		auto buffer = std::stringstream();
		buffer << s << " (thread " << threadNumber << ")" << std::endl;
		Print(buffer);
	}

	static void ChangeData(int& data)
	{
		auto threadNumber = omp_get_thread_num();
		data = 1000 * threadNumber;
	}

	static void Print(const std::stringstream& buffer)
	{
		std::cout << buffer.str();
	}

	static void ShowData(int data)
	{
		std::cout << "Data: " << data << std::endl;
	}
};

int main()
{
	Program::Main();
}