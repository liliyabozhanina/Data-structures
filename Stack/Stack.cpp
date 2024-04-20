// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
	LStack<int> stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);

	std::cout << "Stack elements: ";
	stack.print(); 

	int top;
	stack.push(20);
	std::cout << "Top element of the stack: " << top << std::endl;

	std::cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << std::endl;

	LStack<int> emptyStack;
	emptyStack.top(); 

	return 0;
}



