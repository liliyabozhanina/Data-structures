#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Node 
{
	int value;
	std::vector<Node*> children; 
};

class Tree
{
private:
	Node* root;

public:
	Tree();
	~Tree();
	Tree(const Tree& data);
	Tree& operator=(const Tree& data);

	void createTree(std::string file);
	void helpCreateTree(std::string str, int* arr, int* index);
	bool isDigit(char digit);
	void ignoreSpaces(char*& line); 
	bool hasDuplicates(Tree* data, int x); 

	std::string LOAN(std::string file);
	void SAVE(std::string file) const;
	bool CONTAINS(int arr[], int n, int number); 
	void REMOVE(Tree& data) const;

private:
	Node* copy(Node* r);
	void clear(Node* root);

	friend std::ostream& operator<<(std::ostream& out, const Node& node); 
};
