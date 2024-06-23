#pragma once

#ifndef _BINARY_SEARCH_TREE_INCLUDED
#define _BINARY_SEARCH_TREE_INCLUDED

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <exception>

using namespace std;

template <class T>
class BST
{
public:
	BST();
	BST(const BST<T>&);
	BST<T>& operator=(const BST<T>&);
	~BST();

	BST(const T&, const BST<T>& left, const BST<T>& right);

	void insert(const T& value);
	T& getRoot() const;
	BST<T> getLeft() const;
	BST<T> getRight() const;

	void inorder() const;
	void preorder() const;
	void postorder() const;

	bool isEmpty() const;
	bool isLeaf() const;
	int height() const;

private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;

		Node(const T& data, Node* left = nullptr, Node* right = nullptr)
			: data(data), left(left), right(right) {}
	};

private:
	Node* root;

	BST(Node* newTree);
	void copy(Node*&, Node*);
	void clear(Node*&);
	int height(Node*) const;
	void inorder(Node*) const;
	void preorder(Node*) const;
	void postorder(Node*) const;
};

template<class T>
inline void BST<T>::copy(Node*& newTree, Node* other)
{
	if (other == nullptr)
		newTree = nullptr;
	else
	{
		newTree = new Node(other->data);
		copy(newTree->left, other->left);
		copy(newTree->right, other->right);
	}
}

template<class T>
inline void BST<T>::clear(Node*& tree)
{
	if (tree != nullptr)
	{
		clear(tree->left);
		clear(tree->right);
		delete tree;
		tree = nullptr;
	}
}

template<class T>
inline int BST<T>::height(Node* tree) const
{
	if (tree == nullptr) 
	{
		return 0;
	}
	else
	{
		return 1 + max(height(tree->left), height(tree->right));
	}
}

template<class T>
inline void BST<T>::inorder(Node* r) const
{
	if (r != nullptr)
	{
		inorder(r->left);
		cout << r->data << " ";
		inorder(r->right);
	}
}

template<class T>
inline void BST<T>::preorder(Node* r) const
{
	if (r != nullptr)
	{
		cout << r->data << " ";
		preorder(r->left);
		preorder(r->right);
	}
}

template<class T>
inline void BST<T>::postorder(Node* r) const
{
	if (r != nullptr)
	{
		postorder(r->left);
		postorder(r->right);
		cout << r->data << " ";
	}
}

template<class T>
inline BST<T>::BST() : root(nullptr) {}

template<class T>
inline BST<T>::BST(const BST<T>& other)
{
	if (other.root == nullptr)
	{
		root = nullptr;
	}
	else
	{
		try {
			copy(root, other.root);
		}
		catch (const std::exception & e) {
			root = nullptr;
			cerr << "Exception during copy construction: " << e.what() << endl;
		}
		catch (...) {
			root = nullptr;
			cerr << "Unknown exception during copy construction." << endl;
		}
	}
}

template<class T>
inline BST<T>& BST<T>::operator=(const BST<T>& other)
{
	if (this != &other)
	{
		if (root != nullptr)
		{
			clear(root);
		}
		if (other.root == nullptr)
		{
			root = nullptr;
		}
		else 
		{
			copy(root, other.root);
		}
	}
	return *this;
}

template<class T>
inline BST<T>::~BST()
{
	clear(root);
}

template<class T>
inline BST<T>::BST(Node* newTree) : root(newTree) {}

template<class T>
inline BST<T>::BST(const T& data, const BST<T>& left, const BST<T>& right)
{
	root = new Node(data, left.root, right.root);
}

template <class T>
inline void BST<T>::insert(const T& value) 
{
	Node** current = &root;
	while (*current != nullptr) 
	{
		if (value < (*current)->data)
		{
			current = &((*current)->left);
		}
		else
		{
			current = &((*current)->right);
		}
	}
	*current = new Node(value);
}


template<class T>
inline T& BST<T>::getRoot() const
{
	if (root == nullptr)
	{
		throw runtime_error("The tree is empty.");
	}
	return root->data;
}

template<class T>
inline BST<T> BST<T>::getLeft() const
{
	if (root != nullptr)
	{
		return BST<T>(root->left);
	}
	else
	{
		cerr << "The tree is empty.\n"; //
		exit(1);
	}
}

template<class T>
inline BST<T> BST<T>::getRight() const
{
	if (root != nullptr)
	{
		return BST<T>(root->right);
	}
	else
	{
		cerr << "The tree is empty.\n"; //
		exit(1);
	}
}

template<class T>
inline void BST<T>::inorder() const
{
	inorder(root);
}

template<class T>
inline void BST<T>::preorder() const
{
	preorder(root);
}

template<class T>
inline void BST<T>::postorder() const
{
	postorder(root);
}

template<class T>
inline bool BST<T>::isEmpty() const
{
	return (root == nullptr);
}

template<class T>
inline bool BST<T>::isLeaf() const
{
	bool isLeaf = false;
	if (root != nullptr)
	{
		isLeaf = root->left == nullptr && root->right == nullptr;
	}
	return isLeaf;
}

template<class T>
inline int BST<T>::height() const
{
	return height(root);
}

#endif
