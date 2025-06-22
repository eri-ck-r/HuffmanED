/*
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
	{
		std::cout << "Nao foi possivel abrir o arquivo " << fileName << std::endl;
		return nullptr;
	}
	int* frequencies = new int[256]();
	std::string line{};
	while (std::getline(reader, line, (char)EOF))
	{
		for (auto c : line)

			frequencies[(unsigned int)c]++;

	}
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
			nodes.push_back(new Node{ frequencies[i], (unsigned char)i });
	}
	delete[] frequencies;

	return nodes;
}


#endif // __FileReader_h
*/

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
	FILE* reader = fopen(fileName, "rb");

	int* freq = new int[256]();

	uint8_t byte;  // Vai percorrer cada byte de f
	while(!feof(reader))
	{
		fread(&byte, 1, 1, reader);
		freq[byte]++;
	}

	fclose(reader);
	return freq;
}

std::vector<Node*> getNodes(const char* fileName)
{
	auto frequencies = getFrequencies(fileName);
	std::vector<Node*> nodes;
	for (int i = 0; i < 256; i++)
	{
		if (frequencies[i] > 0)
			nodes.push_back(new Node{ frequencies[i], (uint8_t)i });
	}
	delete[] frequencies;

	return nodes;
}

#endif // __FileReader_h