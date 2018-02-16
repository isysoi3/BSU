// lab1_3_c.cpp: определяет точку входа для консольного приложения.
//

#include "mpi.h"
#include <iostream>
#include <fstream>
#include "Process.h"
using namespace std;

class Program
{
public:
	static void Main()
	{
		ifstream fin("input.txt");
		ofstream fout("output.txt");

		auto process = MPI::Process();

		int* data = new int[3];
		double startwtime = 0.0, endwtime;
		double Result;

		if (process.IsMaster())
		{
			fin >> data[0] >> data[1] >> data[2];
			fin.close();
			startwtime = MPI_Wtime();
		}
		
		MPI_Bcast(data, 3, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);

		double tmp_result = 0;
		double interval = 1.0 * (data[1] - data[0]) / process.ProcessCount();
		double h = 1.0 * (data[1] - data[0]) / data[2];
		double x = data[0] + interval * process.Rank();

		for (int i = 0; i < data[2] / process.ProcessCount(); i++) {
			x += h;
			tmp_result += function(x);
		}
		tmp_result *= h;
		/*for (double x = data[0] + interval * process.Rank(); x < data[0] + interval * (process.Rank() + 1); x+=h)
		while (x < data[0] + interval * (process.Rank() + 1)) {
			x += h;
			tmp_result += f(x);
		}*/

		MPI_Reduce(&tmp_result, &Result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (process.IsMaster())
		{
			fout << "Result: " << Result << endl;
			endwtime = MPI_Wtime();
			fout << "Time: " << (endwtime - startwtime) * 1000 << endl;
			delete[] data;
		}
	}
private:
	static double function(double x)
	{
		return 2 * x + 1;
	}

};

void main()
{
	Program::Main();
}