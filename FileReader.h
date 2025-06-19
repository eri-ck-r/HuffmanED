#ifndef __FileReader_h
#define __FileReader_h

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include "Node.h"
//#define _TEST


int* getFrequencies(const char*);
std::vector<Node*> getNodes(const char*);


int* getFrequencies(const char* fileName)
{
	std::ifstream reader(fileName);
	if (!reader.is_open())
		return nullptr;
	int* frequencies = new int[256]();
	std::string line{};
	while (std::getline(reader, line))
	{
		for (auto c : line)
			frequencies[(int)c]++;
#ifdef _TEST
		std::cout << line << std::endl;
#endif
	}
#ifdef _TEST
	std::cout << std::endl;
	for (int i = 0; i < 256; i++)
		std::cout << "symbol " << (char)i << " freq : " << frequencies[i] << std::endl;
#endif
	reader.close();
	return frequencies;
}

std::vector<Node*> getNodes(const char* fileName)
{
	auto frequencies = getFrequencies(fileName);
	std::vector<Node*> nodes;
	for (int i = 0; i < 256; i++)
	{
		if (frequencies[i] > 0)
			nodes.push_back(new Node{ frequencies[i], (char)i });
	}
	return nodes;
}



#endif // __FileReader_h