#pragma once
#include <iostream>
#include <windows.h>

class SyncHeap
{
private:
	int* heap;
	int size;
	CRITICAL_SECTION csConsole;
	int index;
public:
	SyncHeap(int nSize);            // nSize - размер кучи
	~SyncHeap();

	int* allocate(int nElement);    // получить элементы из кучи
	void free(int* nPtr);           // вернуть элементы в кучу
	void print();                   // печатает массив, для отладки
};

