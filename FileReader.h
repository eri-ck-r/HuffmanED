#ifndef __FileReader_h
#define __FileReader_h

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "MinHeap.h"

std::unique_ptr<unsigned[]> getFrequencies(const char* fileName)
{
	std::ifstream reader(fileName);
	if (!reader.is_open())
		return nullptr;
	auto frequencies = std::make_unique<unsigned[]>(256);
	std::string line{};
	while (std::getline(reader, line))
	{
		for (auto c : line)
			frequencies[(int)c]++;
		
		std::cout << line << std::endl;
	}
	for (int i = 0; i < 256; i++)
		std::cout << "symbol " << (char)i << " freq : " << frequencies[i] << std::endl;

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