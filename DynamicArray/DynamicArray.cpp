// DynamicArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main()
{
	DynamicArray<int> arr;
	arr.push(1);
	arr.push(2);
	arr.push(3);

	cout << "Size: " << arr.get_size() << endl;
	cout << "Capacity: " << arr.get_capacity() << endl;

	if (arr.is_empty())
	{
		cout << "Array is empty." << endl;
	}
	else
	{
		cout << "Array is not empty." << endl;
	}

	int searchElement = 10;
	if (arr.contains(searchElement))
	{
		std::cout << "Element " << searchElement << " is found in the array." << std::endl;
	}
	else
	{
		std::cout << "Element " << searchElement << " is not found in the array." << std::endl;
	}

	/*std::cout << "Elements:" << endl;
	for (size_t i = 0; i < arr.get_size(); ++i)
	{
		std::cout << arr[i] << endl;
	}*/

	arr.delete_elem(1);

	std::cout << "Size: " << arr.get_size() << std::endl;

	arr.destroy();

	if (arr.is_empty())
	{
		std::cout << "Array is empty." << endl;
	}
	else
	{
		std::cout << "Array is not empty." << endl;
	}
  return 0;
}
