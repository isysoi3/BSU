// lab1_2_b.cpp: определяет точку входа для консольного приложения.
//
#include "Process.h"
#include <iostream>
#include <ctime>
#include "mpi.h"



class Program
{
public:
	static void Main1()
	{
		srand(time(NULL));
		auto process = MPI::Process();
		auto sliceSize = 2;
		auto dataLength = process.ProcessCount() * sliceSize;
		double* vector1 = new double[sliceSize];
		double* vector2 = new double[dataLength];
		double Rez = 0;

		Fill(vector2, dataLength);
		MPI_Bcast(vector2, dataLength, MPI_DOUBLE, MPI::MasterRank, MPI_COMM_WORLD);

		if (process.Rank() == 0) {
			SendData(process, sliceSize);
			Fill(vector1, sliceSize);
		}
		else
			MPI_Recv(vector1, sliceSize, MPI_DOUBLE, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		std::cout << "#" << process.Rank() << " (Vector A): ";
		for (int i = 0; i < sliceSize; i++)
			std::cout << vector1[i] << " ";
		std::cout << std::endl << "#" << process.Rank() << " (Vector B): ";

		for (int i = 0; i < sliceSize; i++) {
			std::cout << vector2[i] << " ";
			Rez += vector1[i] * vector2[i];
		}

		double rez = 0;
		MPI_Reduce(&Rez, &rez, 1, MPI_DOUBLE, MPI_SUM, MPI::MasterRank, MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);
		std::cout << std::endl;
		if (process.IsMaster()) {
			std::cout << rez;
			delete[] vector1;
			delete[] vector2;
		}
	}

	static void Main2()
	{
		srand(time(NULL));
		auto process = MPI::Process();

		int bufElems;
		double* vector1 = nullptr;
		double* vector2 = nullptr;
		double tmp_res;
		int dataLength = 0;

		if (process.IsMaster()) {
			auto sliceSize = 2;
			dataLength = process.ProcessCount() * sliceSize;
			SendData(process, sliceSize);
			bufElems = sliceSize;
			vector1 = new double[bufElems];
			Fill(vector1, bufElems);
		}
		else {
			MPI_Status status;
			MPI_Probe(MPI::MasterRank, 0, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_DOUBLE, &bufElems);
			vector1 = new double[bufElems];
			MPI_Recv(vector1, bufElems, MPI_DOUBLE, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		dataLength = bufElems * process.ProcessCount();
		vector2 = new double[dataLength];

		Fill(vector2, dataLength);
		MPI_Bcast(vector2, dataLength, MPI_DOUBLE, MPI::MasterRank, MPI_COMM_WORLD);

		std::cout << "#" << process.Rank() << " got doubles (Vector A): ";
		for (int i = 0; i < bufElems; i++)
			std::cout << vector1[i] << " ";
		std::cout << std::endl << "#" << process.Rank() << " got doubles (Vector B): ";

		tmp_res = 0;
		for (int i = 0; i < bufElems; i++) {
			std::cout << vector2[i] << " ";
			tmp_res += vector1[i] * vector2[i];
		}


		double res = 0;
		MPI_Reduce(&tmp_res, &res, dataLength, MPI_DOUBLE, MPI_SUM, MPI::MasterRank, MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);
		std::cout << std::endl;
		if (process.IsMaster()) {
			std::cout << res << ' ';
			delete[] vector1;
			delete[] vector2;
		}
	}

private:
	static void SendData(const MPI::Process& process, int dataLen) {
		for (auto rank = 1; rank < process.ProcessCount(); ++rank) {
			double* dataA = new double[dataLen];
			Fill(dataA, dataLen);
			MPI_Send(dataA, dataLen, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD);
			delete[] dataA;
		}
	}

	static void Fill(double *data, int size) {
		for (int i = 0; i < size; i++)
			data[i] = (rand() % 10 + 1);
	}
};

void main()
{
	//Program::Main1();
	Program::Main2();
}