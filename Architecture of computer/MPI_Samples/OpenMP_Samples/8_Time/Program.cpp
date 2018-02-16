#include <omp.h>
#include <iostream>
#include <sstream>

class Program
{
public:
	static void Main()
	{
		CalculateTriangleNumberSum(3000, 0);
		CalculateTriangleNumberSum(3000, 1);
		CalculateTriangleNumberSum(3000, 4);
		CalculateTriangleNumberSum(3000, 8);
		CalculateTriangleNumberSum(3000, 16);
	}

private:
	static void CalculateTriangleNumberSum(int n, int threadsCount)
	{
		auto startTime = omp_get_wtime();

		long result = 0;

		#pragma omp parallel for num_threads(threadsCount) reduction(+:result) if(threadsCount > 0)
		for (auto i = 1; i <= n; ++i)
		{
			result += (GetTriangleNumber(i) + GetTriangleNumber(i) + GetTriangleNumber(i)) / 3;
		}

		auto ms = GetEllapsedMilliseconds(startTime);
		std::cout << "Result: " << result << ", time: " << ms << " ms" << std::endl;
	}

	static long GetTriangleNumber(int n)
	{
		long result = 0;
		for (auto i = 1; i <= n; ++i)
		{
			result += i;
		}
		return result;
	}

	static double GetEllapsedMilliseconds(double startTime)
	{
		return (omp_get_wtime() - startTime) * 1000;
	}
};

int main()
{
	Program::Main();
}