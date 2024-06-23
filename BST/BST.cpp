// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main() {
	// Тест на празно дърво
	BST<int> tree;
	cout << "Tree is empty: " << (tree.isEmpty() ? "Yes" : "No") << endl; //Yes

	// Добавяне на елементи
	tree.insert(5);
	tree.insert(3);
	tree.insert(8);
	tree.insert(1);
	tree.insert(4);

	// Проверка на дървото след добавяне на елементи
	cout << "Tree is empty: " << (tree.isEmpty() ? "Yes" : "No") << endl; //No
	cout << "Tree root: " << tree.getRoot() << endl; //5
	cout << "Tree height: " << tree.height() << endl; //3

	// Проверка за обхождане на дървото
	cout << "Inorder: ";
	tree.inorder(); // Трябва да отпечата: 1 3 4 5 8
	cout << endl;

	cout << "Preorder: ";
	tree.preorder(); // Трябва да отпечата: 5 3 1 4 8
	cout << endl;

	cout << "Postorder: ";
	tree.postorder(); // Трябва да отпечата: 1 4 3 8 5
	cout << endl;

	// Тест на копиращия конструктор
	BST<int> copyTree(tree);
	cout << "Copied tree inorder traversal: ";
	copyTree.inorder(); // Трябва да отпечата: 1 3 4 5 8
	cout << endl;

	// Тест на оператора за присвояване
	BST<int> testTree;
	testTree = tree;
	cout << "Tree inorder traversal: ";
	testTree.inorder(); // Трябва да отпечата: 1 3 4 5 8
	cout << endl;

	// Тест на лявото и дясното поддърво
	cout << "Left subtree root: " << tree.getLeft().getRoot() << endl; // Трябва да отпечата: 3
	cout << "Right subtree root: " << tree.getRight().getRoot() << endl; // Трябва да отпечата: 8

	cout << "Tree is leaf: " << (tree.isLeaf() ? "Yes" : "No") << endl; // Трябва да отпечата: No
	BST<int> leafTree;
	leafTree.insert(10);
	cout << "Single node tree is leaf: " << (leafTree.isLeaf() ? "Yes" : "No") << endl; // Трябва да отпечата: Yes

	return 0;
}
