#include "SyncHeap.h"


SyncHeap::SyncHeap(int nSize)
{
	size = nSize;
	heap = new int[size];
	InitializeCriticalSection(&csConsole);
}

SyncHeap::~SyncHeap()
{
	delete[] heap;
	DeleteCriticalSection(&csConsole);
}

int* SyncHeap::allocate(int nElement)
{
	return  (int*)6;
}

void SyncHeap::free(int* nPtr)
{
}

void SyncHeap::print()
{
	EnterCriticalSection(&csConsole);
	for (int i = 0; i < size; i++)
	{
		std::cout << heap[i] << " ";
	}
	LeaveCriticalSection(&csConsole);
}
