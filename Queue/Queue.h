#pragma once

#include <cassert>

#ifndef _QUEUE_INCLUDED
#define _QUEUE_INCLUDED

using namespace std;

template <class T>
class Queue
{
public:
	Queue(); 
	Queue(const Queue& other); 
	Queue& operator=(const Queue& other); 
	~Queue(); 

	void enqueue(const T&); 
	void dequeue(T&); 
	T front() const; 
	bool isEmpty() const; 

private:
	struct Node
	{
		T data;
		Node* next;
		Node(const T& data, Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};
	Node *begin, * end;

private:
	void clear();
	void copy(const Queue&);
};

template<class T>
inline Queue<T>::Queue()
{
	this->begin = nullptr;
	this->end = nullptr;
}

template <class T>
inline Queue<T>::Queue(const Queue& other)
{
	try 
	{
		copy(other);
	}
	catch (...) 
	{
		clear();
		throw;
	}
}

template <class T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other) 
	{
		clear();
		copy(other);
	}
	return *this;
}

template <class T>
inline Queue<T>::~Queue()
{
	this->clear();
}

template<class T>
inline void Queue<T>::enqueue(const T& elem)
{
	Node* p = new Node(elem);
	assert(p != nullptr);
	p->data = elem;
	p->next = nullptr;
	if (end)
	{
		end->next = p;
	} 
	else
	{
		begin = p;
	}
	end = p;
}

template<class T>
inline void Queue<T>::dequeue(T& x)
{
	if (isEmpty())
	{
		cout << "The queue is empty.\n";
		exit(1);
	}
	else
	{
		Node* p = begin;
		x = p->data;
		if (p == end)
		{
			end = nullptr;
			begin = nullptr;
		}
		else begin = p->next;
		delete p;
	}
}

template<class T>
inline T Queue<T>::front() const
{
	if (!isEmpty()) 
	{
		return begin->data;
	}
	throw std::underflow_error("Empty queue");
}

template <class T>
inline bool Queue<T>::isEmpty() const
{
	return this->begin == nullptr;
}

template<class T>
inline void Queue<T>::clear()
{
	while (!isEmpty()) 
	{
		Node* temp = begin;
		begin = begin->next;
		delete temp;
	}
}

template<class T>
inline void Queue<T>::copy(const Queue& r)
{
	begin = end = nullptr;
	while (r) 
	{
		enqueue(r->data);
		r = r->next;
	}
}

#endif
