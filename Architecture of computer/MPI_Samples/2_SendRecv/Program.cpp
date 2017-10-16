#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		// Обычно процесс с рангом 0 считается главным. Он посылает данные другим процессам и собирает их обратно.
		if (process.Rank() == 0)
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
		// Посылаем данные всем остальным процессам.
		for (auto rank = 1; rank < process.ProcessCount(); ++rank)
		{
			int intData = 100 + rank;
			MPI_Send(                // 1a: Посылка данных:
				&intData,            // Указатель на начало данных.
				1,                   // Длина массива данных.
				MPI_INT,             // Тип данных.
				rank,                // Ранг принимающего процесса.
				0,                   // Тэг — номер сообщения (будет рассмотрен далее).
				MPI_COMM_WORLD);     // Группа процессов, в которой идёт работа.

			float floatData = 200.02f + rank;
			MPI_Send(&floatData, 1, MPI_FLOAT, rank, 0, MPI_COMM_WORLD); // 2a.

			double* doubleArrayData = new double[2] { 300.03 + rank, 400.04 + rank };
			MPI_Send(
				doubleArrayData, // 3a: Обратите внимание, что для массивов передаётся сам указатель, без оператора &.
				2, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD);
			delete[] doubleArrayData;
		}
		std::cout << "Sending is finished." << std::endl;
	}

	static void ReceiveData(const MPI::Process& process)
	{
		const int MasterRank = 0;

		// Принимаем данные от главного процесса.

		int intData;
		MPI_Recv(                   // 1b: Приём данных:
			&intData, 				// Указатель на начало данных.
			1, 						// Длина массива данных.
			MPI_INT, 				// Тип данных.
			MasterRank, 			// Ранг отправившего процесса.
			0, 						// Номер сообщения.
			MPI_COMM_WORLD, 		// Группа процессов, в которой идёт работа.
			MPI_STATUS_IGNORE);     // Дополнительная информация (будет рассмотрено далее).
		std::cout << "#" << process.Rank() << " got int: " << intData << std::endl;

		float floatData;
		MPI_Recv(&floatData, 1, MPI_FLOAT, MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // 2b.
		std::cout << "#" << process.Rank() << " got float: " << floatData << std::endl;

		double* doubleArrayData = new double[2];
		MPI_Recv(
			doubleArrayData, // 3b: Как и при передаче, используется сам указатель на начало массива.
			2, MPI_DOUBLE, MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "#" << process.Rank() << " got doubles: " << doubleArrayData[0] << ", " << doubleArrayData[1] << std::endl;
		delete[] doubleArrayData;
	}
};

void main()
{
	Program::Main();
}