#pragma once
#include <iostream>
#include <list>
using namespace std;

template<typename T> 
class Stack {
public:
	virtual ~Stack() {};
	virtual void push(T smth) = 0 ;
	virtual void pop() = 0 ;
	virtual T top() const = 0 ;
	virtual int size() const = 0 ;
	virtual bool isEmpty() const = 0 ;
};

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

template<typename T>
class StackList : public Stack<T> {
private:
	list<T> List;
public:
	StackList();
	virtual ~StackList();
	virtual void push(T smth);
	virtual T top() const;
	virtual void pop();
	virtual bool isEmpty() const;
	virtual int size() const;
};

template<typename T>
StackList<T>::StackList() {
}

template<typename T>
StackList<T>::~StackList() {
}

template<typename T>
void StackList<T>::push(T smth) {
	List.push_back(smth);
}

template<typename T>
T StackList<T>::top() const {
	if (isEmpty())
		throw exception("top is incorrect (stack is empty)");
	return List.back();
}

template<typename T>
void StackList<T>::pop() {
	if (isEmpty())
		throw exception("pop is incorrect (stack is empty)");
	List.pop_back();
}

template<typename T>
bool StackList<T>::isEmpty() const {
	return List.empty();
}

template<typename T>
int StackList<T>::size() const {
	return List.size();
}










/*template<typename T> class StackList : public Stack<T> {
private:
int _size;
struct list {
list *next;
T element;
};
list *t;
public:
StackList();
virtual ~StackList();
virtual void push(T smth);
virtual T top() const;
virtual void pop();
virtual bool isEmpty() const;
virtual int size() const;
};

template<typename T> StackList<T>::StackList() {
t = nullptr;
_size = 0;
}

template<typename T> StackList<T>::~StackList() {
while (t != nullptr) {
list *pos = t;
t = t->next;
delete pos;
}
delete t;
}

template<typename T> void StackList<T>::push(T smth) {
list *pos = new list;
pos->element = smth;
pos->next = t;
t = pos;
_size++;
}

template<typename T> T StackList<T>::top() const{
if (isEmpty())
throw exception("top is incorrect (stack is empty)");
return t->element;
}

template<typename T> void StackList<T>::pop() {
if (isEmpty())
throw exception("pop is incorrect (stack is empty)");
list* pos = t;
t = t->next;
delete pos;
_size--;
}

template<typename T> bool StackList<T>::isEmpty() const {
return t == nullptr;
}

template<typename T> int StackList<T>::size() const {
return _size;
}*/