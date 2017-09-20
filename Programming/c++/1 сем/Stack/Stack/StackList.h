














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