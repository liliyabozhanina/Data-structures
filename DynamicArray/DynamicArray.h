#pragma once

#include <cassert>
#include <algorithm>

#ifndef _DYNAMIC_ARRAY_INCLUDED
#define _DYNAMIC_ARRAY_INCLUDED

using namespace std;

template <class T>
class DynamicArray
{
 public:
	DynamicArray(); 
	~DynamicArray(); 
	DynamicArray(const DynamicArray& other); 
	DynamicArray& operator=(const DynamicArray& other); 

	DynamicArray& operator[](int index); 
	const DynamicArray& operator[](int index) const;

	void push_back(const T& e); 
	bool is_empty() const; 
	bool contains(const T& element) const; 
	void delete_elem(size_t index);  
	void resize(size_t new_capacity);

	size_t get_size() const; 
	size_t get_capacity() const;

private:
	void clear();

private:
	T* data;
	size_t size;
	size_t capacity;

};

template <class T>
inline DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(1)
{
	data = new T[capacity];
}

template <class T>
inline DynamicArray<T>::~DynamicArray()
{
	delete[] data;
}

template <class T>
inline DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
	data = new T[other.capacity];
	size = other.size; 
	capacity = other.capacity;

	try 
	{
		for (int i = 0; i < other.size; i++) 
		{
			data[i] = other.data[i];
		}
	}
	catch (...) 
	{
		delete[] data;
		throw;
	}
}

template <class T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this != other) 
	{
		T* newData = new T[size];
		try 
		{
			for (int i = 0; i < size; i++)
			{
				newData[i] = other.data[i];
			}
		}
		catch (...) 
		{
			delete[] newData;
			throw;
		}

		delete[] data;
		size = other.size;
		data = newData;
	}
	return *this;
}

template <class T>
inline DynamicArray<T>& DynamicArray<T>::operator[](int index)
{
	assert(index < 0 || index >= size);
	if (index < 0 || index >= size) 
	{
		throw std::invalid_argument("Illegal index");
	}
	return data[index];
}

template<class T>
inline const DynamicArray<T>& DynamicArray<T>::operator[](int index) const
{
	assert(index < 0 || index >= size);
	if (index < 0 || index >= size)
	{
		throw std::invalid_argument("Illegal index");
	}
	return data[index];
}

template <class T>
inline bool DynamicArray<T>::contains(const T& element) const
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
inline void DynamicArray<T>::delete_elem(size_t index)
{
	for (size_t i = index; i < size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--size;
}

template <class T>
inline void DynamicArray<T>::clear()
{
	delete[] data; 
	this->data = nullptr; 
	this->size = 0; 
	this->capacity = 0;
}

template <class T>
inline void DynamicArray<T>::resize(size_t new_capacity)
{
	T* temp = new T[new_capacity];
	this->capacity = new_capacity;
	this->size = min(size, new_capacity);

	for (int i = 0; i < size; i++)
	{
			temp[i] = data[i];
	}
	delete[] data; 
	data = temp;
}

template <class T>
inline void DynamicArray<T>::push_back(const T& e)
{
	if (size >= capacity) 
	{
		resize(2*capacity);
	}
	
	data[size] = e; 
	++size;
}

template <class T>
inline size_t DynamicArray<T>::get_size() const
{
	return size;
}

template <class T>
inline size_t DynamicArray<T>::get_capacity() const
{
	return capacity;
}

template <class T>
inline bool DynamicArray<T>::is_empty() const
{
	return size == 0;
}

#endif
