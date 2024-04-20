// Queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Queue.h"

int main()
{
	Queue<int> queue;

	if (queue.isEmpty()) 
	{
		cout << "The queue is empty.\n";
	}

	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);

	int frontElement = queue.front();
	cout << "Front element: " << frontElement << endl;

	int dequeuedElement;
	queue.dequeue(dequeuedElement);
	cout << "Dequeued element: " << dequeuedElement << endl;

	frontElement = queue.front();
	cout << "Front element after dequeue: " << frontElement << endl;

	queue.enqueue(4);
	queue.enqueue(5);
  
	if (!queue.isEmpty())
	{
		cout << "The queue is not empty.\n";
	}

	while (!queue.isEmpty())
	{
		queue.dequeue(dequeuedElement);
		cout << "Dequeued element: " << dequeuedElement << endl;
	}

	if (queue.isEmpty()) 
	{
		cout << "The queue is empty.\n";
	}

	return 0;
}
