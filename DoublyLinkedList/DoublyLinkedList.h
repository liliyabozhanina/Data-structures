#pragma once
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

using namespace std;

class DoublyLinkedList
{
private:
	struct Node
	{
		int value;
		Node* next;
		Node* prev;

		Node(int value_node, Node* next_node = nullptr, Node* prev_node = nullptr)
		{
			this->value = value_node;
			this->next = next_node;
			this->prev = prev_node;
		}
	};

	Node* first;
	Node* last;
	Node* current;
	size_t size;

	void copy_list(const DoublyLinkedList&); 
	void delete_list(); 
public:
	friend ostream& operator<<(ostream&, const DoublyLinkedList&); 

	DoublyLinkedList(); 
	DoublyLinkedList(const DoublyLinkedList&); 
	DoublyLinkedList& operator=(const DoublyLinkedList&); 
	~DoublyLinkedList(); 

	DoublyLinkedList operator+(const int&) const; 
	DoublyLinkedList& operator+=(const int&); 

	void push_front(int value); 
	void push_back(int value); 
	void push_before(int value, int before); 
	void push_after(int value, int after); 

	void pop_front(); 
	void pop_back(); 
	void delete_node(int current); 

	size_t get_size() const; 
	int length(int len); 
	bool empty() const;
	bool contains(int element) const;
	void print() const; 
	void reverse(); 

};

#endif 
