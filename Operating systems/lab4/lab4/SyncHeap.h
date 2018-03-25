#pragma once
#include <iostream>
#include <windows.h>

class SyncHeap
{
private:
	int* heap;
	int size;
	CRITICAL_SECTION csConsole, csArray;
	HANDLE mutex, emptySemaphore, fullSemaphore;
public:
	SyncHeap(int nSize);            
	~SyncHeap();

	void allocate(int nElement, int element);    
	void free(int element);          
	void print();                
};

