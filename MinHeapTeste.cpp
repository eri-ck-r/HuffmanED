#include "MinHeap.h"

int main()
{
	MinHeap mh("teste.txt");
	std::cout << mh.size() << std::endl;
	mh.escreve_niveis();
	while (mh.size() != 0)
	{
		std::cout << " minHeap size =  " << mh.size() << std::endl;
		mh.extrai_minimo()->print();
	}

}