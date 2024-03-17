#pragma once

#ifndef _DYNAMIC_ARRAY_INCLUDED
#define _DYNAMIC_ARRAY_INCLUDED

using namespace std;

template <class T>
class DynamicArray
{
private:
	T* data;
	size_t size; 
  size_t capacity; 
public:
	DynamicArray(); 
	~DynamicArray(); 
	DynamicArray(const DynamicArray& other); 
	DynamicArray& operator=(const DynamicArray& other); 
	DynamicArray& operator[](int index); 

	void push(const T& e); 
	bool is_empty() const; 
	bool contains(const T& element) const; 
	void delete_elem(size_t index); 
	void destroy(); 
	void resize(size_t new_capacity);

	size_t get_size() const; 
	size_t get_capacity() const;

};

template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(1)
{
	data = new T[capacity];
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete[] data;
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
	data = new T[other.capacity];
	size = other.size; 
	capacity = other.capacity;

	for (int i = 0; i < other.size; i++) 
	{
		data[i] = other.data[i];
	}
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this != other) 
	{
		delete[] data; 
		size = other.size; 
		data = new T[size]; 
		if (!data) 
		{
			cout << "Memory allocation error!" << endl;
		}

		for (int i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}
	}
	return *this; 
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		cout << "Illegal index!" << endl;
	}
	return data[index]; 
}

template <class T>
bool DynamicArray<T>::contains(const T& element) const
{
	for (int i = 0; i < size; i++) 
	{
		if (data[i] == element)
		{
			return true;
		}
	}
	return false; 
}


template <class T>
void DynamicArray<T>::delete_elem(size_t index)
{
	for (size_t i = index; i < size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--size;
}

template <class T>
void DynamicArray<T>::destroy()
{
	delete[] data; 
	this->data = nullptr; 
	this->size = 0; 
	this->capacity = 0;
}

template <class T>
void DynamicArray<T>::resize(size_t new_capacity)
{
	T* temp = new T[new_capacity];
	this->capacity = new_capacity;

	for (int i = 0; i < size; i++)
	{
			temp[i] = data[i];
	}
	delete[] data; 
	data = temp;
}

template <class T>
void DynamicArray<T>::push(const T& e)
{
	if (size >= capacity) 
	{
		resize(capacity);
	}
	if (size + 1 >= capacity) 
	{
		resize(capacity); 
	}

	if (size == 0) 
	{
		resize(capacity); 
	}

	for (int i = size; i > 0; i--) 
	{
		data[i] = data[i - 1];
	}
	data[0] = e; 
	++size;
}

template <class T>
size_t DynamicArray<T>::get_size() const
{
	return size;
}

template <class T>
size_t DynamicArray<T>::get_capacity() const
{
	return capacity;
}

template <class T>
bool DynamicArray<T>::is_empty() const
{
	if (size == 0) 
	{
		return true;
	}
	else
	{
		return false; 
	}
}

#endif
