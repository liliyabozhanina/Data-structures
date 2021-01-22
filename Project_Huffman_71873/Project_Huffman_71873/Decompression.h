#pragma once
#ifndef  DECOMPRESSION_H_
#define DECOMPRESSION_H_

#include "HuffmanTree.h"
#include "Compression.h"


class Decompression
{
	string huffTree;
	string filePath;
	int numberOfBits;
public:
	Decompression(string filePath) { this->filePath = filePath; this->numberOfBits = 0; }

	void setOutputFile(string filePath) { this->filePath = filePath; }
	void decompressFile(string inputFilePath);

private:
	string decompressString(queue<cChar> inputString);
	void writeToFile(string outputString);

};
#endif
