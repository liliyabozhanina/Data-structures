#pragma once
#include <cassert>
#include <string>

template <typename T>
class Queue
{
public:
	Queue(); 
	~Queue(); 
	Queue(const Queue<T>&); 
	Queue<T>& operator=(const Queue<T>&); 

	bool empty() const;
	bool full() const;
	void push(const T&); 
	void pop(T&); 
	void head(T&) const; 
	unsigned size() const; 

private:
	unsigned front;
	unsigned rear; 
	unsigned queueSize;
	unsigned queueLen; 
	T* arr; 
  
	void copyQueue(const Queue<T>&); 
	void deleteQueue();
};

template <typename T>
Queue<T>::Queue()
{
	front = 0; 
	rear = 0;
	queueSize = 0;
	queueLen = 0;
	arr = new T[queueSize];
	assert(arr != NULL);
}

template <typename T>
Queue<T>::~Queue()
{
	deleteQueue();
}

template <typename T>
Queue<T>::Queue(const Queue<T>& r)
{
	//arr == NULL;
	copyQueue(r);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& r)
{
	if (this != &r)
	{
		deleteQueue();
		copyQueue(r);
	}
	return this*;
}

template <typename T>
void Queue<T>::copyQueue(const Queue<T>& r)
{
	assert(arr != NULL);
	queueSize = r.queueSize;
	queueLen = r.queueLen;
	arr = new T[queueSize];
	front = r.front;
	rear = r.rear;
	for (unsigned i = 0; i < queueSize; i++)
	{
		arr[i] = r.arr[i];
	}
}

template <typename T>
void Queue<T>::deleteQueue()
{
	delete[] arr;
}

template <typename T>
bool Queue<T>::empty() const
{
	return queueLen == 0;
}

template <typename T>
bool Queue<T>::full() const
{
	return queueLen == queueSize;
}

template <typename T>
void Queue<T>::push(const T& x)
{
	if (!full())
	{
		arr[rear] = x;
		queueLen++;
		rear++;
		rear = rear % queueSize;
	}
	else
	{
		cout << "Queue is full\n";
		exit(1);
	}
}

template <typename T>
void Queue<T>::pop(T& x)
{
	if (!empty())
	{
		x = arr[front];
		queueLen--;
		front--;
		front = front % queueSize;
	}
	else
	{
		cout << "Empty queue\n";
		exit(1);
	}
}

template<typename T>
void Queue<T>::head(T& x) const
{
	if (!empty())
	{
		x = arr[front];
	}
	else
	{
		cout << "Empty queue\n";
		exit(1);
	}
}

template <typename T>
unsigned Queue<T>::size() const
{
	return queueLen;
}
