#include "SyncHeap.h"


SyncHeap::SyncHeap(int nSize, CRITICAL_SECTION _csConsole)
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
	csConsole = _csConsole;
}

SyncHeap::~SyncHeap()
{
	delete[] heap;
	CloseHandle(fullSemaphore);
	CloseHandle(emptySemaphore);
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
	for (int i = 0; i < nElement; i++)
		WaitForSingleObject(emptySemaphore, INFINITY);
	que.push(std::make_pair(nElement, element));
	for (int i = 0; i < size && k > 0; i++)
	{
		EnterCriticalSection(&csArray);
		if (heap[i] == 0) {
			heap[i] = element;
			k--;
		}
		LeaveCriticalSection(&csArray);
	}
	ReleaseSemaphore(fullSemaphore, nElement, NULL);
}

void SyncHeap::free(int element)
{

	std::pair<int, int> pair;
	while (true) {
		pair = que.front();
		que.pop();
		if (pair.second == element) {
			break;
		}
		que.push(pair);
	}
	int k = pair.first;
	for (int i = 0; i < pair.first; i++)
		WaitForSingleObject(fullSemaphore, INFINITY);
	for (int i = 0; i < size && k > 0 ; i++)
	{
		EnterCriticalSection(&csArray);
		if (heap[i] == element) {
			heap[i] = 0;
			k--;
		}
		LeaveCriticalSection(&csArray);
	}
	ReleaseSemaphore(emptySemaphore, pair.first, NULL);

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
