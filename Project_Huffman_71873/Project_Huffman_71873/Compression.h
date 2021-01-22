#pragma once
#ifndef COMPRESSION_H_
#define COMPRESSION_H_

#include "HuffmanTree.h"
#include <fstream>

typedef pair<char, string> cPair;
typedef unsigned char cChar;

class Compression
{
	list<cPair> charMap;
	string filePath;
public:
	Compression(string filePath);
	~Compression() {}
	void compressString(string input);
	void compressFile(string inputFilePath);
	void setOutputFile(string);

private:
	string mapString(string input);
	string findSymbol(char in);
	string convertTree(HuffmanTree& tree);
	void writeToFile(string outputString, int numberOfBits, string tree);
	void recursiveSearch(Tree* root, string code);
	string toBitString(string);
};

#endif