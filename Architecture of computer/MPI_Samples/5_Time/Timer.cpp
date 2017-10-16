#include "Timer.h"
#include <mpi.h>

namespace MPI
{
	Timer::Timer()
	{
		_startTime = MPI_Wtime();
	}

	double Timer::Seconds() const
	{
		return MPI_Wtime() - _startTime;
	}
}