#include "SyncHeap.h"


SyncHeap::SyncHeap(int nSize)
{
	index = 0;
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
	//TODO 
	int *rez = new int[nElement];
	return  rez;
}

void SyncHeap::free(int* nPtr)
{
	//TODO 
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
