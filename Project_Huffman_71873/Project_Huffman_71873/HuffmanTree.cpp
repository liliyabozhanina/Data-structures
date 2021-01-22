#include <iostream>
#include "HuffmanTree.h"

using namespace std;

bool Tree::operator<(Tree const& B) const
{
	if (this->frequency == B.frequency)
		return this->symbol != NULL && B.symbol == NULL;
	return this->frequency < B.frequency;
}

void FrequencyTable::push(char symbol)
{
	if (map.empty())
	{
		map.push_back(uPair(symbol, 1));
	}
	else
	{
		auto iter = map.begin();
		while (iter != map.end() && iter->first != symbol)
		{
			iter++;
		}
		if (iter == map.end())
		{
			map.push_back(uPair(symbol, 1));
		}
		else
		{
			iter->second++;
		}
	}
}

void FrequencyTable::mapString(string inputString)
{
	for (int i = 0; i < inputString.size(); i++)
	{
		this->push(inputString.c_str()[i]);
	}
}

Tree::Tree(int freq, char sym) : frequency(freq), left(NULL), right(NULL), symbol(sym) {}
Tree::Tree(int freq, Tree* _left, Tree* _right) : frequency(freq), left(_left), right(_right), symbol(NULL) {}


FrequencyTable HuffmanTree::buildMap(string inputString)
{
	FrequencyTable result(inputString);
	return result;
}

void HuffmanTree::buildTree(FrequencyTable ftmap)
{
	auto iter = ftmap.begin();
	priority_queue<Tree*, vector<Tree*>, Compare> trees;
	for (int i = 0; i < ftmap.size(); i++)
	{
		trees.push(new Tree(iter->second, iter->first));
		iter++;
	}
	Tree* tempLeft;
	Tree* tempRight;
	Tree* temp;
	while (trees.size() > 1)
	{
		tempLeft = trees.top();
		trees.pop();
		tempRight = trees.top();
		trees.pop();
		temp = new Tree((tempLeft->frequency + tempRight->frequency), tempLeft, tempRight);
		trees.push(temp);
	}
	if (!trees.empty())
	{
		treeRoot = trees.top();
		trees.pop();
	}
}