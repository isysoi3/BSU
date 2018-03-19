#include "SyncHeap.h"


SyncHeap::SyncHeap(int nSize)
{
	size = nSize;
	heap = new int[size];
	emptySemaphore = CreateSemaphore(NULL, size, size, NULL);
	fullSemaphore = CreateSemaphore(NULL, 0, size, NULL);
	for (int i = 0; i < size; i++)
	{
		heap[i] = 0;
	}
	InitializeCriticalSection(&csArray);
	InitializeCriticalSection(&csConsole);
}

SyncHeap::~SyncHeap()
{
	delete[] heap;
	DeleteCriticalSection(&csConsole);
	DeleteCriticalSection(&csArray);
}

void SyncHeap::allocate(int nElement, int element)
{
	while (true) {
		if (!ReleaseSemaphore(emptySemaphore, -nElement, NULL)) {
			EnterCriticalSection(&csArray);
			int k = nElement;
			for (int i = 0; i < size && k >= 0; i++)
			{
				if (heap[i] == 0) {
					heap[i] = element;
					k--;
				}
			}
			LeaveCriticalSection(&csArray);
			!ReleaseSemaphore(fullSemaphore, nElement, NULL);
			break;
		}

	}
}

void SyncHeap::free(int element)
{
	EnterCriticalSection(&csArray);
	int k = 0;
	for (int i = 0; i < size && k >= 0; i++)
	{
		if (heap[i] == element) {
			heap[i] = 0;
			k++;
		}
	}
	LeaveCriticalSection(&csArray);
	ReleaseSemaphore(emptySemaphore, k, NULL);
	ReleaseSemaphore(fullSemaphore, -k, NULL);
}

void SyncHeap::print()
{
	EnterCriticalSection(&csConsole);
	for (int i = 0; i < size; i++)
	{
		std::cout << heap[i] << " ";
	}
	std::cout << std::endl; 
	LeaveCriticalSection(&csConsole);
}
