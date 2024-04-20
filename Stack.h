#pragma once

#ifndef _LINKED_STACK_INCLUDED
#define _LINKED_STACK_INCLUDED

using namespace std;

template <typename T>
class LStack
{
public:
	LStack(); 
	~LStack();
	LStack(const LStack&);
	LStack& operator=(const LStack&);

	bool isEmpty() const; 
	void push(int elem); 
	void pop(); 
	const T& top() const; 
	void print() const; 
	size_t getSize() const; 
private:
	void copy(const LStack&); 
	void clear(); 

private:
	struct Node 
	{
		int data; 
		Node* next; 

		Node(int data, Node* next = nullptr) 
		{
			this->data = data;
			this->next = next;
		}
	};

	Node* topElement; 
private:
	size_t size;
};

template<typename T>
inline LStack<T>::LStack()
{
	this->topElement = nullptr;
	this->size = 0;
}

template <typename T>
inline LStack<T>::~LStack()
{
	this->clear();
}

template <typename T>
inline LStack<T>::LStack(const LStack<T>& s) 
{
	this->copy(s);
}

template <typename T>
inline LStack<T>& LStack<T>::operator=(const LStack<T>& s)
{
	if (this != &s)
	{
		clear();
		copy(s);
	}
	return *this;
}

template<typename T>
inline bool LStack<T>::isEmpty() const
{
	return this->topElement == nullptr;
}

template<typename T>
inline void LStack<T>::push(int elem)
{
	Node* newNode = new Node(elem); 
	if (topElement != nullptr)
	{
		newNode->next = topElement;
	}
	this->topElement = newNode; 
	this->size++;
}

template<typename T>
inline void LStack<T>::pop()
{
	if (isEmpty())
	{
		throw std::out_of_range("Stack is empty!");
	}
	LStack<T>::Node* temp = this->topElement; 
	elem = this->topElement->data; 

	this->topElement = this->topElement->next;
	this->size--;
	delete this->temp; 
}

template<typename T>
inline const T& LStack<T>::top() const
{
	if (isEmpty())
	{
		throw std::out_of_range("Stack is empty.");
	}
	return this->topElement->data;
}

template<typename T>
inline size_t LStack<T>::getSize() const
{
	return size;
}

template<typename T>
inline void LStack<T>::copy(const LStack<T>& s)
{
	LStack<T>::Node* temp = s.topElement; 
	while (this->temp != nullptr)
	{
		push(this->temp->data); 
		this->temp = this->temp->next;
	}
}

template<typename T>
inline void LStack<T>::clear()
{
	LStack<T>::Node* temp = nullptr;
	while (this->topElement != nullptr)
	{
	    temp = this->topElement->next;
		delete this->topElement;
		this->topElement = temp;
	}
	this->size = 0;
}

/*template<typename T>
inline void LStack<T>::print()
{
	LStack<T>::Node* current = this->topElement; 
	while (current != nullptr)
	{
		cout << current->data << " "; 
		current = current->next; 
	}
	cout << endl; 
}*/

#endif
