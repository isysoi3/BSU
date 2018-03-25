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
	CloseHandle(fullSemaphore);
	CloseHandle(emptySemaphore);
	DeleteCriticalSection(&csConsole);
	DeleteCriticalSection(&csArray);
}

void SyncHeap::allocate(int nElement, int element)
{
	if (nElement > size)
	{
		std::cout << "The heap size is smaller" << std::endl;
		return;
	}
	
	int k = nElement;

	while (true) {
		if (ReleaseSemaphore(fullSemaphore, nElement, NULL) != 0) {
			for (int i = 0; i < size && k > 0; i++)
			{
				EnterCriticalSection(&csArray);
				if (heap[i] == 0) {
					WaitForSingleObject(emptySemaphore, INFINITY);
					heap[i] = element;
					k--;
				}
				LeaveCriticalSection(&csArray);
			}
			break;
		}
	}
	

}

void SyncHeap::free(int element)
{
	
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		EnterCriticalSection(&csArray);
		if (heap[i] == element) {
			WaitForSingleObject(fullSemaphore, INFINITY);
			heap[i] = 0;
			k++;
		}
		LeaveCriticalSection(&csArray);
	}
	ReleaseSemaphore(emptySemaphore, k, NULL);
	
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
