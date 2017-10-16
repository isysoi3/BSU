#include "Data.h"
#include <mpi.h>

namespace MPI
{
	void Send(const double* data, int length, int destinationRank, int tag)
	{
		MPI_Send(data, length, MPI_DOUBLE, destinationRank, tag, MPI_COMM_WORLD);
	}

    void Receive(double* data, int length, int sourceRank, int tag)
	{
		MPI_Recv(data, length, MPI_DOUBLE, sourceRank, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	double* ReceiveDoubleArray(int length, int sourceRank, int tag)
	{
		double* data = new double[length];
		Receive(data, length, sourceRank, tag);
		return data;
	}

	void Broadcast(double* data, int length, int rootRank)
	{
		MPI_Bcast(data, length, MPI_DOUBLE, rootRank, MPI_COMM_WORLD);
	}
}