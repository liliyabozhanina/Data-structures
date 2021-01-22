#pragma once
#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include <iostream>
#include <list>
#include <string>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

typedef pair<char, int> uPair;
typedef list<uPair>::iterator iter;

class FrequencyTable
{
	list<uPair> map;
public:
	FrequencyTable() {}

	FrequencyTable(string inputString)
	{
		this->mapString(inputString);
	}

	~FrequencyTable() {}

	void mapString(string inputString);

	iter begin()
	{
		return map.begin();
	}

	iter end()
	{
		return map.end();
	}

	int size()
	{
		return map.size();
	}

private:
	void push(char symbol);
};

struct Tree
{
	int frequency;
	Tree* left, * right;
	char symbol;
	Tree(int, char);
	Tree(int, Tree*, Tree*);
	~Tree() {}
	bool operator<(Tree const& B) const;

	bool isLeaf()
	{
		return left == NULL && right == NULL;
	}
	void destroy()
	{
		if (left != NULL && !left->isLeaf())
		{
			left->destroy();
			delete left;
		}
		if (right != NULL && !right->isLeaf())
		{
			right->destroy();
			delete right;
		}
	}
};

class Compare
{
public:
	bool operator() (const Tree* A, const Tree* B) const
	{
		if (A->frequency == B->frequency)
			return B->symbol != NULL && A->symbol == NULL;
		return A->frequency > B->frequency;
	}
};

class HuffmanTree
{
	Tree* treeRoot;
public:
	HuffmanTree(string inputString)
	{
		this->buildTree(buildMap(inputString));
	}

	~HuffmanTree()
	{
		treeRoot->destroy();
	}

	Tree* root()
	{
		return treeRoot;
	}
private:
	FrequencyTable buildMap(string inputString);
	void buildTree(FrequencyTable);
};

#endif
