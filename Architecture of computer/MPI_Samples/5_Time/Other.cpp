#include "Other.h"
#include <mpi.h>

namespace MPI
{
	void Barrier()
	{
		MPI_Barrier(MPI_COMM_WORLD);
	}
}