/********************************************
 *
 * Nathan de Almeida Rezende
 * Luiz Alexandre Espíndola Cunha
 * Erick Rodrigues de Lemos Ribeiro
 * Trabalho de Estrutura de Dados
 * Professor(a): Diego Padilha Rubert
 *
 */

#ifndef __FileReader_h
#define __FileReader_h

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include "Node.h"

/**
 * Função para calcular as frequências de cada byte
 * no arquivo original, é usado na compactação.
 * Recebe o nome do arquivo a ser aberto e devolve
 * um vetor com as frequências calculadas
 */
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

/**
 * Função para transformar o vetor simples de
 * frequências de bytes em um vector de Nodes.
 * Recebe o vetor simples de frequências calculado
 * na função acima e devolve um vector de Nodes
 * para ser posteriormente organizado em MinHeap
 */
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