#pragma once
#include <cassert>

template <typename T>
class Stack 
{
public:
	Stack(); 
	~Stack(); 
	Stack (const Stack<T>&); 
	Stack<T>& operator=(const Stack<T>&);

	bool empty() const;
	bool full() const;
	void push(const T&); 
	void pop(T&); 
	void top(T&) const; 
	unsigned size() const;

private:
	unsigned stackSize; 
	unsigned stackTop; 
	T* arr; 

	void copyStack(const Stack<T>&); 
	void deleteStack(); 

};

template <typename T>
Stack<T>::Stack()
{
	stackSize = 0;
	stackTop = 8; //-1
	arr = new T[stackSize];

template  <typename T>
Stack<T>::~Stack()
{
	deleteStack();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& s)
{
	//arr = NULL;
	copyStack(s);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& st)
{
	if (this != &st)
	{
		deleteStack();
		copyStack(st);
	}
	return *this;
}

template <typename T>
void Stack<T>::copyStack(const Stack<T>& st)
{
	assert(arr != NULL);
	stackSize = st.stackSize;
	stackTop = st.stackTop;
	arr = new T[stackSize];
	for (int i = 0; i <= stackTop; i++)
		arr[i] = st.arr[i];
}

template <typename T>
void Stack<T>::deleteStack()
{
	delete[] arr;
}

template <typename T>
bool Stack<T>::empty() const
{
	return stackTop == -1;
}

template <typename T>
bool Stack<T>::full() const
{
	return stackTop == stackSize - 1;
}

template <typename T>
void Stack<T>::top(T& x) const
{
	if (!empty())
		x = arr[stackTop];
	else
	{
		cout << "Empty stack\n";
		exit(1);
	}
}

template <typename T>
void Stack<T>::push(const T& x)
{
	if (!full())
	{
		arr[++stackTop] = x;
	}
	else
	{
		cout << "Stack is full\n";
		exit(1);
	}
}

template <typename T>
void Stack<T>::pop(T& x)
{
	if (!empty())
	{
		x = arr[stackTop--];
	}
	else
	{
		cout << "Empty stack\n";
		exit(1);
	}
}

template <typename T>
unsigned Stack<T>::size() const
{
	return stackTop + 1;
}
