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
		int value; //informacionna chast na spisuk
		Node* next; //adresna chast (ukazatel kum vuzel na spisuk)

		Node(int value_node, Node* next_node = nullptr) //konstruktor na vuzel na spisuk
		{
			this->value = value_node;
			this->next = next_node;
		}
	};

	Node* first; //ukazatel kum purviq element
	Node* last; //ukazatel kum posledniq element
	Node* current; //ukazatel kum tekusht vuzel
	size_t size; //broi vuzli v spisuk(razmer)

	//pomoshtni funkcii
	void copy_list(const SinglyLinkedList&); //kopira spisuk
	void delete_list(); //iztriva spisuk
public:
	friend ostream& operator<<(ostream&, const SinglyLinkedList&); //predefinirane na operaciqta << za klasa 

	SinglyLinkedList(); //konstruktor
	SinglyLinkedList(const SinglyLinkedList&); //konstruktor za kopirane
	SinglyLinkedList& operator=(const SinglyLinkedList&); //predefinirane na operaciqta =
	~SinglyLinkedList(); //destruktor

	//dobavqne na vuzel v spisuka
	void push_front(int value); //dobavq vuzel v nachaloto
	void push_back(int value); //dobavq vuzel v kraq

	//premahvane na vuzel ot spisuka
	void pop_front(); //iztriva purviq vuzel
	void pop_back(); //iztriva posledniq vuzel
	void delete_node(int current); //iztriva vuzel po ukazana stoinost

	size_t get_size() const; //broi vuzli v spisuk(razmer)
	int length() const; //obhojda i prebroqva elementite na spisuk, bez da go razrushava
	bool empty() const; //proverka dali spisukut e prazen
	bool contains(int element) const;
	void print() const; //izvejda elementite na spisuka
	void concat(const SinglyLinkedList&); //konkatenaciq na lineini spisuci
	void reverse(); //obrushtane na elementite na spisuk

};

#endif 