#pragma once
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>

using namespace std;

class SinglyLinkedList
{
private:
	struct Node
	{
		int value; 
		Node* next; 

		Node(int value_node, Node* next_node = nullptr) 
		{
			this->value = value_node;
			this->next = next_node;
		}
	};

	Node* first; 
	Node* last; 
	Node* current; 
	size_t size; 

	//pomoshtni funkcii
	void copy_list(const SinglyLinkedList&); 
	void delete_list(); 
public:
	friend ostream& operator<<(ostream&, const SinglyLinkedList&); 

	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList&); 
	SinglyLinkedList& operator=(const SinglyLinkedList&);
	~SinglyLinkedList();

	void push_front(int value); 
	void push_back(int value); 

	void pop_front(); 
	void pop_back(); 
	void delete_node(int current); 

	size_t get_size() const; 
	int length() const; 
	bool empty() const; 
	bool contains(int element) const;
	void print() const; 
	void concat(const SinglyLinkedList&); 
	void reverse(); 

};

#endif 
