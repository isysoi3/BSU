#pragma once
#pragma once
#include <iostream>
//class Stack {
//public:
//    virtual ~Stack() = 0;
//    virtual void push() = 0;
//    virtual int pop() = 0;
//	virtual int top() = 0;
//	//virtual int size() = 0;
//    virtual bool isEmpty() = 0;    
//};
//
//template<class T> class StackLists : public Stack {
//private:
//	 struct node{
//		T element;
//		Node *next;
//	};
//	 node *head;
//	 node *tail;
//public: 
//	StackLists(heaad = 0, tail = 0);
//};
// 

template<typename T> class StackArray {
private:
	T *stack;
	int t;
public:
	StackArray(int size);
	virtual ~StackArray() {
		delete[]stack;
	};
	virtual void push(T smth) {
		stack[++t] = smth;
	};
	virtual void pop() {
		if (isEmpty())
			std::cout << "stack is empty";
		else
			t--;
	};
	virtual bool isEmpty() {
		return top() == 0;
	};
	virtual T top() {
		return stack[t];
	};
	virtual int size() {
		return t + 1;
	}
};

