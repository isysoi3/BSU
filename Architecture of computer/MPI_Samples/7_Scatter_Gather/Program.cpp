#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		double* data = nullptr;
		auto sliceSize = 20;
		auto dataLength = process.ProcessCount() * sliceSize;

		if (process.IsMaster())
		{
			data = new double[dataLength];
			Fill(data, dataLength);
		}

		auto buffer = new double[sliceSize];
		MPI_Scatter(		   // 1: Разрезает массив на равные куски и пересылает каждому процессу свой кусок:
			data, 			   // Исходный массив (для мастер-процесса), для остальных процессов не используется.
			sliceSize, 		   // Размер куска (для мастер-процесса), для остальных процессов не используется.
			MPI_DOUBLE, 	   // Тип данных (для мастер-процесса), для остальных процессов не используется.
			buffer, 		   // Массив, куда будет записываться кусок.
			sliceSize, 		   // Размер куска.
			MPI_DOUBLE, 	   // Тип данных.
			MPI::MasterRank,   // Ранг раздающего процесса.
			MPI_COMM_WORLD);   // Рабочая группа.

		std::cout << "Process #" << process.Rank() << " has buffer[" << sliceSize - 1 << "] = " << buffer[sliceSize - 1] << std::endl;

		ChangeData(buffer, sliceSize); // 2. Изменяем кусок.

		MPI_Gather(            // 3. Собираем куски в главном процессе:
			buffer, 		   // Кусок.
			sliceSize, 		   // Размер куска.
			MPI_DOUBLE, 	   // Тип данных.
			data, 			   // Массив, в который будут склеиваться куски (для мастер-процесса), для остальных процессов не используется.
			sliceSize, 		   // Размер куска (для мастер-процесса), для остальных процессов не используется.
			MPI_DOUBLE, 	   // Тип данных (для мастер-процесса), для остальных процессов не используется.
			MPI::MasterRank,   // Ранг собирающего процесса.
			MPI_COMM_WORLD);   // Рабочая группа.

		if (process.IsMaster())
		{
			std::cout << "data[" << dataLength - 1 << "] = " << data[dataLength - 1] << std::endl;
			delete[] data;
		}

		data = new double[dataLength];
		MPI_Allgather(buffer, sliceSize, MPI_DOUBLE, data, sliceSize, MPI_DOUBLE, MPI_COMM_WORLD); // 4: Gather + Broadcast.
		delete[] buffer;
		std::cout << "Process #" << process.Rank() << " has data[" << dataLength - 1 << "] = " << data[dataLength - 1] << std::endl;
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

	static void ChangeData(double* data, int length)
	{
		for (auto i = 0; i < length; ++i)
		{
			data[i] += 1000;
		}
	}
};

void main()
{
	Program::Main();
}