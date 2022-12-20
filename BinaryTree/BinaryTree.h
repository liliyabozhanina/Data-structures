#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <cstdlib>

template<typename T>
class BinaryTree
{
private:
	struct Node
	{
		T data; 
		Node *left; 
		Node *right; 

		Node(const T& data, Node *left = nullptr, Node *right = nullptr)
		{
			data = data;
			left = left;
			right = right;
		}
	};

private:
	Node* root;

	BinaryTree(Node* newTree); 
	void copyTree(Node*&, Node*);

	void deleteTree(Node*&);
	int height(Node*) const; 
	void inorder(Node*) const; 
	void preorder(Node*) const; 
	void postorder(Node*) const;

public:
	BinaryTree(); 
	BinaryTree(const BinaryTree<T> &); 
	BinaryTree<T>& operator=(const BinaryTree<T>&);
	~BinaryTree(); 

	BinaryTree(const T&, const BinaryTree<T>& left, const BinaryTree<T>& right);


	T& getRoot() const; 
	BinaryTree<T> getLeft() const; 
	BinaryTree<T> getRight() const; 

	
	void inorder() const; 
	void preorder() const; 
	void postorder() const; 

	bool isEmpty() const; 
	bool isLeaf() const; 
	int height() const; 
};

#endif 
