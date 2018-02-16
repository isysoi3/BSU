#include <mpi.h>
#include <iostream>
#include "Process.h"
#include "Data.h"
#include "Other.h"
#include "Timer.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		int dataLength = 10000;
		double* data = new double[dataLength];
		if (process.IsMaster())
		{
			Fill(data, dataLength);
		}

		auto bcastTime = UseBroadcast(process, data, dataLength);
		auto sendRecvTime = UseSendReceive(process, data, dataLength);

		if (process.IsMaster())
		{
			std::cout << "bcast spends " << bcastTime << " seconds." << std::endl;
			std::cout << "send/recv spends " << sendRecvTime << " seconds." << std::endl;
			std::cout << "difference: " << sendRecvTime / bcastTime << " times." << std::endl;
			// –азница может быть намного значительнее, если дл€ вычислений используютс€ несколько машин.
		}
		else
		{
			std::cout << "data[2] = " << data[2] << std::endl;
		}

		delete[] data;
	}

private:
	static void Fill(double* data, int length)
	{
		for (auto i = 0; i < length; ++i)
		{
			data[i] = i + 0.25;
		}
	}

	static double UseBroadcast(const MPI::Process& process, double* data, int dataLength)
	{
		MPI::Barrier();
		auto time = MPI_Wtime();   // 1: ѕолучить количество секунд с момента запуска процесса.

		MPI::Broadcast(data, dataLength, MPI::MasterRank);

		MPI::Barrier();
		return MPI_Wtime() - time; // 2: ¬рем€ бродкаста.
	}

	static double UseSendReceive(const MPI::Process& process, double*& data, int dataLength)
	{
		MPI::Barrier();
		auto timer = MPI::Timer();

		if (process.IsMaster())
		{
			for (auto rank = 1; rank < process.ProcessCount(); ++rank)
			{
				MPI::Send(data, dataLength, rank, 0);
			}
		}
		else
		{
			MPI::Receive(data, dataLength, MPI::MasterRank, 0);
		}

		MPI::Barrier();
		return timer.Seconds();
	}
};

void main()
{
	Program::Main();
}