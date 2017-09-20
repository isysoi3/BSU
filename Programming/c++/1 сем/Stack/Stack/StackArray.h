#include "Stack.h"
#pragma once


template<typename T>
class StackArray : public Stack<T> {
private:
	T *stack;
	int t;
	int max_s;
public:
	StackArray(int size);
	virtual ~StackArray();
	virtual void push(T smth);
	virtual void pop();
	virtual T top() const;
	virtual bool isEmpty() const;
	virtual int size() const;
};

template<typename T>
StackArray<T>::StackArray(int asize) {
	if (asize < 1)
		throw invalid_argument("size <= 0");
	stack = new T[asize];
	max_s = asize;
	t = -1;
}

template<typename T>
StackArray<T>::~StackArray() {
	delete[]stack;
}

template <typename T>
void StackArray<T>::push(T smth) {
	if (t == max_s - 1)
		throw exception("push is incorrect (stack is full)");
	stack[++t] = smth;
}

template <typename T>
void StackArray<T>::pop() {
	if (isEmpty())
		throw exception("pop is incorrect (stack is empty)");
	t--;
}

template <typename T>
T StackArray<T>::top() const {
	if (isEmpty())
		throw exception("top is incorrect (stack is empty)");
	return stack[t];
}

template <typename T> bool
StackArray<T>::isEmpty() const {
	return t == -1;
}

template <typename T>
int StackArray<T>::size() const {
	return t + 1;
}

