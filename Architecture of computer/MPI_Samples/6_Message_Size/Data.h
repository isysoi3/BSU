#pragma once

namespace MPI
{
	void Send(const double* data, int length, int destinationRank, int tag);
	void Receive(double* data, int length, int sourceRank, int tag);
	double* ReceiveDoubleArray(int length, int sourceRank, int tag);
	
	void Broadcast(double* data, int length, int rootRank);
}