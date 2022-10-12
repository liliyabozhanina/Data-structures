#include <iostream>
#include "SinglyLinkedList.h"

void SinglyLinkedList::copy_list(const SinglyLinkedList& other_list)
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
	//suzdavane(kopirane) na purviq vuzel
	current = other_list.first;
	first = new Node(current->value);
	last = first;

	current = current->next;
	while (current != nullptr)
	{
		copy = new Node(current->value); //suzdava se nov vuzel
		last->next = copy; //noviqt vuzel e naslednik na predishniq
		last = copy;
		current = current->next;
	}
	size = other_list.size;
}

void SinglyLinkedList::delete_list()
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

SinglyLinkedList::SinglyLinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->current = nullptr;
	this->size = 0;
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other_list)
{
	this->first = nullptr;
	this->copy_list(other_list);
}

SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& r)
{
	if (this != &r)
	{
		this->delete_list();
		this->copy_list(r);
	}
	return *this;
}

SinglyLinkedList::~SinglyLinkedList()
{
	this->delete_list();
}

void SinglyLinkedList::push_front(int value)
{
	if (first != nullptr)
	{
		first = new Node(value, first);
	}
	else
	{
		first = new Node(value, first);
		last = first;
	}
	++size;
}

void SinglyLinkedList::push_back(int value)
{
	if (first == nullptr)
	{
		first = new Node(value);
		last = first;
		++size;
		return;
	}
	//dobavqne na nov vuzel sled tekushtiq posleden
	Node* last_value = last;
	last_value->next = new Node(value);
	last = last_value->next;
	++size;
}

void SinglyLinkedList::pop_front()
{
	if (first == nullptr)
	{
		return;
	}
	else if (first->next == nullptr)
		last = nullptr; //spisukut ne e prazen, no ima samo edin vuzel

	Node * p = this->first;
	first = first->next;
	delete p;
	--size;
}

void SinglyLinkedList::pop_back()
{
	if (first == nullptr)
	{
		return;
	}
	else if (first->next == nullptr)
	{
		delete first;
		first = nullptr;
		last = nullptr; //spisukut ne e prazen, no ima samo edin vuzel
		--size;
		return;
	}

	Node* last_value = this->first;
	Node* prev_value = nullptr; //adres na predposledniq vuzel

	while (last_value->next != nullptr)
	{
		prev_value = last_value;
		last_value = last_value->next;
	}
	//last = prev_value;
	prev_value->next = nullptr;
	delete last_value;
	--size;
}

void SinglyLinkedList::delete_node(int current)
{
	if (first == nullptr)
	{
		return;
	}
	if (first->value == current)
	{
		Node* p = this->first; //trqbva da se iztrie purviqt vuzel
		if (first->next != nullptr)
		{
			first = first->next;
		}
		else //spisukut ima samo edin vuzel
		{
			first = nullptr;
			last = nullptr;
		}
		delete p;
		--size;
		return;
	}
	//tursene na elementa, koito trqbva da se iztrie
	Node* delete_node = this->first;
	while (delete_node->next != nullptr && delete_node->next->value != current)
	{
		delete_node = delete_node->next;
	}
	if (delete_node->next != nullptr)
	{
		Node* p = delete_node->next; //adres na vuzela za iztrivane
		delete_node->next = delete_node->next->next;
		delete p;
		--size;
		return;
	}
}

size_t SinglyLinkedList::get_size() const
{
	return this->size;
}

int SinglyLinkedList::length() const
{
	int len = 0;
	Node* p = this->first;
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}

ostream& operator<<(ostream& output, const SinglyLinkedList& other_list)
{
	SinglyLinkedList::Node* p = other_list.first;
	while (p != nullptr) {
		output << p->value << " ";
		p = p->next;
	}
	return output;
}

bool SinglyLinkedList::empty() const
{
	return this->first == nullptr;
}

bool SinglyLinkedList::contains(int element) const
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

void SinglyLinkedList::print() const
{
	Node* p = first;
	while (p) 
	{
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

void SinglyLinkedList::concat(const SinglyLinkedList& r)
{
	Node* p = r.first;
	while (p)
	{
		push_back(p->value);
		p = p->next;
	}
}

void SinglyLinkedList::reverse()
{
	Node* p;
	Node* prev_value;
	Node* temp;
	p = first;
	if (p)
	{
		prev_value = nullptr;
		temp = first;
		first = last;
		last = temp;
		while (p != first)
		{
			temp = p->next;
			p->next = prev_value;
			prev_value = p;
			p = temp;
		}
		p->next = prev_value;
	}
}
