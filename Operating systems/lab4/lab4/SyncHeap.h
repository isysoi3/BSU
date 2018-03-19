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
	SyncHeap(int nSize);            // nSize - ðàçìåð êó÷è
	~SyncHeap();

	void allocate(int nElement, int element);    // ïîëó÷èòü ýëåìåíòû èç êó÷è
	void free(int element);           // âåðíóòü ýëåìåíòû â êó÷ó
	void print();                   // ïå÷àòàåò ìàññèâ, äëÿ îòëàäêè
};

