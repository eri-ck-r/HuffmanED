#include "FileReader.h"

int main()
{
	auto v = getFrequencies("seila.txt");
	for (int i = 0; i < 256; i++)
		std::cout << v[i] << std::endl;
}