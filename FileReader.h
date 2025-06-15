#ifndef __FileReader_h
#define __FileReader_h

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "MinHeap.h"

int* getFrequencies(const char* fileName)
{
	std::ifstream reader(fileName);
	if (!reader.is_open())
		return nullptr;
	int frequencies[256]{};
	std::string line{};
	while (std::getline(reader, line))
	{
		for (auto c : line)
			frequencies[(int)c]++;
#ifdef _DEBUG
		std::cout << line << std::endl;
#endif
	}
#ifdef _DEBUG
	for (int i = 0; i < 256; i++)
		std::cout << "symbol " << (char)i << " freq : " << frequencies[i] << std::endl;
#endif
	reader.close();
	return frequencies;
}

auto getNodes(const char* fileName)
{
	auto frequencies = getFrequencies(fileName);
	std::vector<Node*> nodes;
	for(int i = 0; i < 256; i++)
	{
		if(frequencies[i] > 0)
			nodes.push_back(new Node{frequencies[i], (char)i});
	}
	return nodes;
}



#endif // __FileReader_h