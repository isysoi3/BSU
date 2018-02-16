#include "Stack.h"
#include <iostream>

using namespace std;

template<typename T> StackArray<T>::StackArray(int size) {
	stack = new T[size];
	t = -1;
}
