#include <cstdio>
#include "FileReader.h"
#include "HuffmanTree.h"
#include "MinHeap.h"
#include "HuffmanTable.h"
#include "BufferBits.h"

using namespace std;

int main(int argc, char* argv[])
{
	FILE* f1 = fopen(argv[1], "rb");
	FILE* f2 = fopen(argv[2], "wb");

	BufferBitsLeitura buffer_leitura(f1);  // Não usa new, não é Java
	BufferBitsEscrita buffer_escrita(f2);  // Não usa new, não é Java
	while (!feof(f1))
	{
		uint8_t byte_lido = 0;
		for (int i = 0; i < 8; i++)  // Constrói um byte inteiro a partir de bits lidos
		{
			byte_lido |= buffer_leitura.le_bit();
		}

		for (int i = 0; i < 8; ++i)  // Escreve bit a bit a partir de byte inteiro construido anteriormente
		{
			uint8_t bit = (byte_lido & (1 << (7 - i))) != 0 ? 1 : 0;
			buffer_escrita.escreve_bit(bit);
		}
	}

	fclose(f1);
	fclose(f2);
	return 0;
}