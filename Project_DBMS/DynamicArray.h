#pragma once

template <class DataType>
class DynamicArray
{
public:
	DynamicArray(); 
	~DynamicArray(); 
	DynamicArray(const DynamicArray<DataType>& other); 
	DynamicArray<DataType>& operator=(const DynamicArray<DataType>& other); 

	void push_back(const DataType&); 
	unsigned getSize() const; 
	unsigned getCapacity() const; 
	void deleteElement(); 

private:
  unsigned size = 0;
	unsigned capacity = 8;
	DataType* data;

	void init(); 
	void resize(); 
	void copy(const DynamicArray&);
};

template<class DataType>
DynamicArray<DataType>::DynamicArray()
{
	init();
}

template<class DataType>
DynamicArray<DataType>::~DynamicArray()
{
	deleteElement();
}

template<class DataType>
DynamicArray<DataType>::DynamicArray(const DynamicArray& other)
{
	init();
	copy(other);
}

template<class DataType>
DynamicArray<DataType>& DynamicArray<DataType>::operator=(const DynamicArray& other)
{
	if (this != &other)
	{
		deleteElement();
		copy(other);
	}
	return *this;
}

template <class DataType>
void DynamicArray<DataType>::push_back(const DataType& element)
{
	if (size >= capacity)
	{
		resize();
	}
	data[size++] = element;
}

template<class DataType>
unsigned DynamicArray<DataType>::getSize() const
{
	return size;
}

template<class DataType>
unsigned DynamicArray<DataType>::getCapacity() const
{
	assert(capacity != 0);
	return capacity;
}

template<class DataType>
void DynamicArray<DataType>::init()
{
	data = NULL;
	size = 0;
	capacity = 8;
}

template<class DataType>
void DynamicArray<DataType>::deleteElement()
{
	delete[] data;
	data = NULL;
	size = 0;
	capacity = 8;
}

template<class DataType>
void DynamicArray<DataType>::copy(const DynamicArray& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new DataType[capacity];
	for (unsigned i = 0; i < size; ++i)
	{
		data[i] = other.data[i];
	}
}

template <class DataType>
void DynamicArray<DataType>::resize()
{
	capacity *= 2;
	DataType* newData = new DataType[capacity];
	for (unsigned i = 0; i < size; ++i)
	{
		newData[i] = data[i];
	}
	deleteElement();
	data = newData;
}
