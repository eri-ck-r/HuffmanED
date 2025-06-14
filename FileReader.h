#ifndef __FileReader_h
#define __FileReader_h
#include <iostream>
#include <fstream>
#include <string>

constexpr int* getFrequencies(const char* fileName)
{
	std::ifstream reader(fileNggame);
	if (!reader.is_open())
		return nullptr;
	static int frequencies[256]{};
	std::string line{};
	while (std::getline(reader, line))
	{
		for (auto c : line)
			frequencies[(int)*c]++;
		std::cout << line << std::endl;
	}
	for (int i = 0; i < 256; i++)
		std::cout << "symbol " << (char)i << " freq : " << frequencies[i] << std::endl;

	return frequencies;
}


#endif // __FileReader_h