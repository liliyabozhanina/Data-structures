#include <iostream>
#include "DoublyLinkedList.h"

void DoublyLinkedList::copy_list(const DoublyLinkedList& other_list)
{
	Node* copy;
	Node* current;
	if (first != nullptr)
		delete_list();
	if (other_list.first == nullptr)
	{
		first = nullptr;
		last = nullptr;
		current = nullptr;
		size = 0;
		return;
	}
	current = other_list.first;
	first = new Node(current->value);
	last = first;

	current = current->next;
	while (current != nullptr)
	{
		copy = new Node(current->value);
		last->next = copy;
		copy->prev = last;
		last = copy;
		current = current->next;
	}
	size = other_list.size;
}

void DoublyLinkedList::delete_list()
{
	Node* p;
	while (first != nullptr)
	{
		p = first;
		first = first->next;
		delete p;
	}
	last = nullptr;
	size = 0;
}

DoublyLinkedList::DoublyLinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->current = nullptr;
	this->size = 0;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other_list)
{
	this->copy_list(other_list);
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& r)
{
	if (this != &r)
	{
		this->delete_list();
		this->copy_list(r);
	}
	return *this;
}

DoublyLinkedList::~DoublyLinkedList()
{
	this->delete_list();
}

DoublyLinkedList DoublyLinkedList::operator+(const int& r) const
{
	DoublyLinkedList result = (*this);
	result += r;
	return result;
}

DoublyLinkedList& DoublyLinkedList::operator+=(const int& r) 
{
	Node* ptr_first = new DoublyLinkedList::Node(r, first, nullptr);
	first->prev = ptr_first;
	first = ptr_first;
	return *this;
}

void DoublyLinkedList::push_front(int value)
{
	if (first == nullptr)
	{
		first = new Node(value, first);
		last = first;
	}
	else
	{
		Node* first_value = first;
		first = new Node(value, first);
		first_value->prev = first;
	}
	++size;
}

void DoublyLinkedList::push_back(int value)
{
	if (first == nullptr)
	{
		first = new Node(value);
		last = first;
		++size;
		return;
	}
	Node* last_value = last;
	last_value->next = new Node(value, nullptr, last);
	last = last_value->next;
	++size;
}

void DoublyLinkedList::push_before(int value, int before)
{
	Node* current = this->first;
	Node* new_value = new Node(value);

	while (current != nullptr && current->value != before)
	{
		current = current->next;
	}

	if (current->prev == nullptr)
	{
		new_value->next = current;
		current->prev = new_value;
		this->first = new_value;
	}
	else 
	{
		new_value->next = current;
		new_value->prev = current->prev;
		current->prev->next = new_value;
		current->prev = new_value;
	}
}

void DoublyLinkedList::push_after(int value, int after)
{
	if (this->first == nullptr) 
	{
		return;
	}
	Node* current = this->first;
	Node* new_value = new Node(value);

	while (current != nullptr && current->value != after)
	{
		current = current->next;
	}
	if (current->next == nullptr)
	{
		current->next = new_value;
		new_value->prev = current;
	}
	else 
	{
		new_value->next = current->next;
		new_value->prev = current;
		current->next = new_value;
		current->next->prev = new_value;
	}
}

void DoublyLinkedList::pop_front()
{
	if (first == nullptr)
	{
		return;
	}
	else if (first->next == nullptr)
		last = nullptr;

	Node* p = this->first;
	first = first->next;
	delete p;
	--size;
}

void DoublyLinkedList::pop_back()
{
	if (first == nullptr)
	{
		return;
	}
	else if (first->next == nullptr)
	{
		delete first;
		first = nullptr;
		last = nullptr;
		--size;
		return;
	}

	Node* last_value = this->last;
	Node* prev_value = last->prev;
	last = last_value;
	last->next = nullptr;
	delete last_value;
	--size;
}

void DoublyLinkedList::delete_node(int current)
{
	if (first == nullptr)
	{
		return;
	}
	if (first->value == current)
	{
		Node* p = this->first;
		if (first->next != nullptr)
		{
			first = first->next;
		}
		else
		{
			first = nullptr;
			last = nullptr;
		}
		delete p;
		--size;
		return;
	}
	Node* delete_node = this->first;
	while (delete_node->next != nullptr && delete_node->next->value != current)
	{
		delete_node = delete_node->next;
	}
	if (delete_node->next != nullptr)
	{
		Node* p = delete_node->next;
		delete_node->next = delete_node->next->next;
		(p->next)->prev = delete_node;
		delete p;
		--size;
		return;
	}
}

size_t DoublyLinkedList::get_size() const
{
	return this->size;
}

int DoublyLinkedList::length(int len)
{
	int length = 0;
	if (this->first == nullptr) 
	{
		return length;
	}

	if (this->first->value == len) 
	{
		length++;
	}

	Node* cur = this->first;

	while (cur->next != nullptr) 
	{
		cur = cur->next;

		if (cur->value ==len) 
		{
			length++;
		}
	}
	return length;
}

bool DoublyLinkedList::empty() const
{
	return this->first == nullptr;
}

bool DoublyLinkedList::contains(int element) const
{
	Node* p = this->first;

	while (p != nullptr)
	{
		if (p->value == element)
		{
			return true;
		}
		p = p->next;
	}

	return false;
}


ostream& operator<<(ostream& output, const DoublyLinkedList& other_list)
{
	DoublyLinkedList::Node* p = other_list.first;
	while (p != nullptr) 
	{
		output << p->value << " ";
		p = p->next;
	}
	return output;
}

void DoublyLinkedList::print() const
{
	Node* p = first;
	while (p)
	{
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

void DoublyLinkedList::reverse()
{
	Node* p = this->first;
	Node* copy = nullptr;

	while (p != nullptr) 
	{
		copy = p->prev;
		p->prev = p->next;
		p->next = copy;
		p = p->prev;
	}

	if (copy != nullptr) 
	{
		this->first = copy->prev;
	}
}
