#include <mpi.h>
#include <iostream>
#include "Process.h"

namespace MPI
{
	// ќбЄртки дл€ пересылки данных.

	void Send(int data, int destinationRank, int tag)
	{
		MPI_Send(&data, 1, MPI_INT, destinationRank, tag, MPI_COMM_WORLD);
	}

	int ReceiveInt(int sourceRank, int tag)
	{
		int data;
		MPI_Recv(&data, 1, MPI_INT, sourceRank, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		return data;
	}
}

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		if (process.IsMaster())
		{
			SendData(process);
		}
		else
		{
			ReceiveData(process);
		}
	}

private:
	static void SendData(const MPI::Process& process)
	{
		for (auto rank = 1; rank < process.ProcessCount(); ++rank)
		{
			MPI::Send(300 + rank, rank, 2); // 1a: ѕоследний аргумент Ч тэг, номер сообщени€.
			MPI::Send(200 + rank, rank, 1); // 2a
			MPI::Send(100 + rank, rank, 0); // 3a
		}
		std::cout << "Sending is finished." << std::endl;
	}

	static void ReceiveData(const MPI::Process& process)
	{
		// “эги позвол€ют нам принимать сообщени€ в нужном пор€дке.
		std::cout << "#" << process.Rank() << " got int 0: " << MPI::ReceiveInt(MPI::MasterRank, 0) << std::endl; // 3b
		std::cout << "#" << process.Rank() << " got int 1: " << MPI::ReceiveInt(MPI::MasterRank, 1) << std::endl; // 2b
		std::cout << "#" << process.Rank() << " got int 2: " << MPI::ReceiveInt(MPI::MasterRank, 2) << std::endl; // 1b
	}
};

void main()
{
	Program::Main();
}