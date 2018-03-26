#pragma once
#include <iostream>
#include <windows.h>
#include <queue> 

class SyncHeap
{
private:
	int* heap;
	int size;
	CRITICAL_SECTION csConsole, csArray;
	HANDLE emptySemaphore, fullSemaphore;
	std::queue<std::pair<int,int>> que;
public: 
	SyncHeap(int nSize, CRITICAL_SECTION _csConsole);
	~SyncHeap();

	void allocate(int nElement, int element);    
	void free(int element);          
	void print();                
};

