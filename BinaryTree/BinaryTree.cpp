#include "BinaryTree.h"

template<typename T>
void BinaryTree<T>::copyTree(Node*& newTree, Node* other)
{
	if (other == nullptr)
		newTree = nullptr;
	else
	{
		newTree = new Node();
		newTree->data = other->data;
		copyTree(newTree->left, other->left);
		copyTree(newTree->right, other->right);
	}
}

template<typename T>
void BinaryTree<T>::deleteTree(Node*& tree)
{
	if (tree != nullptr)
	{
		deleteTree(tree->left);
		deleteTree(tree->right);
		tree = nullptr;
	}
}

template<typename T>
int BinaryTree<T>::height(Node* tree) const
{
	if (tree == nullptr)
		return 0;
	else
		return 1 + max(height(tree->left), height(tree->right));
}

template<typename T>
void BinaryTree<T>::inorder(Node* r) const
{
	if (r != nullptr)
	{
		inorder(r->left);
		process(r);
		inorder(r->right);
	}
}

template<typename T>
void BinaryTree<T>::preorder(Node* r) const
{
	if (r != nullptr)
	{
		process(r);
		preorder(r->left);
		preorder(r->right);
	}
}

template<typename T>
void BinaryTree<T>::postorder(Node* r) const
{
	postorder(r->left);
	postorder(r->right);
	process(r);
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	if (other.getRoot == nullptr)
		root = nullptr;
	else
		copyTree(root, other.root);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
	if (this != &other)
	{
		if (root != nullptr)
			deleteTree(root);
		if (other.root == nullptr)
			root = nullptr;
		else
			copyTree(root, other.root);
	}
	return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	deleteTree(root);
}

template<typename T>
BinaryTree<T>::BinaryTree(Node* newTree)
{
	root = newTree;
}

template<typename T>
BinaryTree<T>::BinaryTree(const T&, const BinaryTree<T>& left, const BinaryTree<T>& right)
{
	root = new Node<T>(this->data, left.root, right.root);
}

template<typename T>
T& BinaryTree<T>::getRoot() const
{
	return root->value;
}

template<typename T>
BinaryTree<T> BinaryTree<T>::getLeft() const
{
	if (root != nullptr)
		return BinaryTree<T>(root->left);
	else
	{
		std::cout << "The tree is empty.\n";
		exit(1);
	}
}

template<typename T>
BinaryTree<T> BinaryTree<T>::getRight() const
{
	if (root != nullptr)
		return BinaryTree<T>(root->right);
	else
	{
		std::cout << "The tree is empty.\n";
		exit(1);
	}
}

template<typename T>
void BinaryTree<T>::inorder() const
{
	inorder(root);
}

template<typename T>
void BinaryTree<T>::preorder() const
{
	preorder(root);
}

template<typename T>
void BinaryTree<T>::postorder() const
{
	postorder(root);
}

template<typename T>
bool BinaryTree<T>::isEmpty() const
{
	return(root == nullptr);
}

template<typename T>
bool BinaryTree<T>::isLeaf() const
{
	bool isLeaf = false;
	if (root != nullptr)
		isLeaf = root->left == nullptr && root->right == nullptr;
	return isLeaf;
}

template<typename T>
int BinaryTree<T>::height() const
{
	return height(root);
}
