#include "Compression.h"

Compression::Compression(string filePath)
{
	this->filePath = filePath;
}

void Compression::compressString(string input)
{
	string tempTree = this->mapString(input);

	string compressedString;
	cChar mask = 128, temp = 0;
	int stringPos = 0, bytePos = 0, numberOfBits = 0;
	string encoding;

	for (int i = 0; i < input.size(); i++)
	{
		char c = input.c_str()[i];
		encoding = findSymbol(input.c_str()[i]);
		for (int enPos = 0; enPos < encoding.size(); enPos++)
		{
			if (bytePos == 8)
			{
				mask = 128;
				bytePos = 0;
				compressedString += temp;
				temp = 0;
			}
			if (encoding.c_str()[enPos] == '1')
			{
				mask >>= bytePos++;
				temp |= mask;
				mask = 128;
				numberOfBits++;
			}
			else
			{
				bytePos++;
				numberOfBits++;
			}
		}
	}

	compressedString += temp;
	int originalSize = input.size() * 8;
	string bitString = toBitString(compressedString);
	cout << "Achieved " << ((numberOfBits * 100) / originalSize) << "% compression compared to original size!" << endl
		<< "Compressed string in bits : " << bitString << endl
		<< "Compressed string as bytes : ";
	for (int i = 0; i < compressedString.size(); i++)
		cout << (int)compressedString.c_str()[i] << " ";
	cout << endl;
	this->writeToFile(compressedString, numberOfBits, tempTree);
}

void Compression::compressFile(string inputFilePath)
{
	ifstream readStream;
	string input;
	readStream.open(inputFilePath, ios_base::in);
	char character;
	while (readStream.get(character))
	{
		input += character;
	}
	readStream.close();
	this->compressString(input);
}

void Compression::setOutputFile(string filePath)
{
	this->filePath = filePath;
}

void Compression::recursiveSearch(Tree* root, string code)
{
	if (root->symbol != NULL) {
		charMap.push_back(cPair(root->symbol, code));
		return;
	}
	recursiveSearch(root->left, (code + '0'));
	recursiveSearch(root->right, (code + '1'));
}

string Compression::toBitString(string inputString)
{
	string output;
	cChar mask = 128, temp;
	for (int i = 0; i < inputString.size(); i++)
	{
		temp = inputString.c_str()[i];
		while (mask >= 1) {
			if ((temp & mask) == 0)
				output += '0';
			else
				output += '1';
			mask >>= 1;
		}
		mask = 128;
	}
	return output;
}

string Compression::mapString(string input)
{
	HuffmanTree tree(input);
	recursiveSearch(tree.root(), string());
	return convertTree(tree);
}

string Compression::findSymbol(char in)
{
	auto iter = charMap.begin();
	while (iter != charMap.end() && iter->first != in)
	{
		iter++;
	}
	if (iter == charMap.end())
		return string();
	return iter->second;
}

/*
* Конвертира дърво в последователност от символи в string.
* Дървото се записва като пълно двоично дърво като празните места
* се записват с '\0'.
*/
string Compression::convertTree(HuffmanTree& tree)
{
	string result;
	queue<Tree*> nodeQueue;
	int leavesReached = 0;

	nodeQueue.push(tree.root());
	while (leavesReached < charMap.size())
	{
		if (nodeQueue.front() == NULL)
		{
			result += (char)0;
			nodeQueue.push(NULL);
			nodeQueue.push(NULL);
			nodeQueue.pop();
		}
		else {
			if (nodeQueue.front()->symbol != NULL)
			{
				result += nodeQueue.front()->symbol;
				leavesReached++;
			}
			else
				result += (char)0;
			nodeQueue.push(nodeQueue.front()->left);
			nodeQueue.push(nodeQueue.front()->right);
			nodeQueue.pop();
		}
	}
	return result;
}

void Compression::writeToFile(string outputString, int numberOfBits, string tree)
{
	ofstream writeStream;
	writeStream.open(filePath.c_str(), ios_base::out | ios_base::binary | ios_base::trunc);

	writeStream.write(reinterpret_cast<char*>(&numberOfBits), sizeof(int));
	for (int i = 0; i < tree.size(); i++)
		writeStream.write((&tree.c_str()[i]), sizeof(char));
	writeStream.write((char*)"\a", sizeof(char));
	for (int i = 0; i < outputString.size(); i++)
		writeStream.write((&outputString.c_str()[i]), sizeof(char));
	writeStream.close();
}