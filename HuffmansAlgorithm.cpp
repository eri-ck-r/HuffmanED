#include <fstream>
#include "FileReader.h"
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "HuffmanTable.h"
#include "BufferBits.h"
#include <iostream>

// remover essa classe e só tranformar compact e discompact em
// funçoes normais? pq uma classe sem atributo não faz muito sentido.
// daria pra usar namespace ao invés de uma classe
class HuffmansAlgorithm
{
public:
	static void compact(char* argv[]);
	static void discompact(char* argv[]);

private:
	static void discompactSimb(HuffmanTree& t, FILE* f, BufferBitsLeitura&);
};

int main(int argc, char* argv[])
{
	if (argv[1][0] == 'c')
		HuffmansAlgorithm::compact(argv);
	else
		HuffmansAlgorithm::discompact(argv);

	return 0;
}

void HuffmansAlgorithm::compact(char* argv[])
{
	auto nodes = getNodes(argv[2]);

	MinHeap mh(nodes);

	HuffmanTree tree(mh);

	HuffmanTable table(tree);

	if (DEBUG_BITS)
	{
		for (size_t i = 0; i < table.codes.size(); i++)
		{
			printf("%c ", (char)i);
			for (size_t j = 0; j < table.codes[i].size(); j++)
				std::cout << table.codes[i][j] << " ";
			printf("\n");
		}
	}

	uint16_t alphabet_size = table.leaves.size();

	// Cria arquivo compactado
	FILE* compacted = fopen(argv[3], "wb");
	fwrite(&alphabet_size, 2, 1, compacted);

	uint8_t zero = 0;
	fwrite(&zero, 1, 1, compacted);

	auto alphabet = table.leaves.data();
	fwrite(alphabet, sizeof(alphabet[0]), alphabet_size, compacted);

	// A partir daqui tem que escrever bit a bit (usar BufferBits)
	BufferBitsEscrita write_buffer(compacted);

	for (int i = 0, size = table.treeCode.size(); i < size; ++i) // Adiciona os bits do percurso em ordem da árvore de Huffman
		write_buffer.escreve_bit(table.treeCode[i]);

	// Compactação em si do "texto" original
	FILE* original = fopen(argv[2], "rb");
	uint8_t original_byte;
	while (fread(&original_byte, 1, 1, original) == 1)
	{
		std::vector<bool> simb_code(table.codes[original_byte]);

		if (DEBUG_BITS)
		{
			printf("Escrevendo %c ", original_byte);
			for (auto i : simb_code)
				std::cout << i;
			putchar('\n');
		}

		for (auto bit : simb_code) // Compacta o byte original
			write_buffer.escreve_bit(bit);
	}

	if(write_buffer.livres() != 8)
	{
		uint8_t last_byte_bits = write_buffer.livres(); // Guarda os bits de sobra do último byte
	
		write_buffer.descarrega(); // Escreve o último byte
	
		fseek(compacted, 2, SEEK_SET);
		fwrite(&last_byte_bits, 1, 1, compacted);
	}

	fclose(compacted);
	fclose(original);
}

void HuffmansAlgorithm::discompact(char* argv[])
{
	FILE* compacted = fopen(argv[2], "rb");
	FILE* discompacted = fopen(argv[3], "wb");

	// Faz a leitura do tamanho do "alfabeto" do arquivo compactado
	uint16_t alphabet_size;
	fread(&alphabet_size, 2, 1, compacted);

	// Guarda quanto bits de sobra tem o último byte compactado
	uint8_t last_byte_bits;
	fread(&last_byte_bits, 1, 1, compacted);

	// Guarda os símbolos do "alfabeto"
	uint8_t* alphabet = new uint8_t[alphabet_size]();
	fread(alphabet, sizeof(alphabet[0]), alphabet_size, compacted);

	// Lê o código da árvore
	BufferBitsLeitura read_buffer(compacted);
	std::vector<bool> treeCode;
	for (int i = 0, n = 0; n < alphabet_size; ++i)
	{
		treeCode.push_back(read_buffer.le_bit());
		if (treeCode[i] == 1)
			++n;
	}
	
	// Bem ineficiente, considero trocar a tipagem de vários vectors em HuffmanTable
	std::vector<unsigned char> leaves;
	for (int i = 0; i < alphabet_size; ++i)
		leaves.push_back(alphabet[i]);

	if (DEBUG_BITS)
	{
		std::cout << "codigo da arvore debug " << std::endl;
		for(size_t i = 0; i < treeCode.size(); ++i)
		{
			std::cout << treeCode[i];
		}
		std::cout << std::endl;
		std::cout << "os bagulho dentro de leaves : " << std::endl;
		for(int i = 0; i < alphabet_size; ++i)
		{
			printf("%c", leaves[i]);
		}
		std::cout << std::endl;
	}

	HuffmanTree tree(treeCode, leaves);
	tree.escreve_bfs();

	std::cout << "compacted = " << compacted << std::endl;

	long beginning, end;
	
	beginning = ftell(compacted);

	fpos_t cur_pos;
	fgetpos(compacted, &cur_pos);

	fseek(compacted, 0,  SEEK_END);

	end = ftell(compacted);

	fsetpos(compacted, &cur_pos);

	std::cout << "beginning = " << beginning << std::endl;
	std::cout << "      end = " << end << std::endl;

	
	while(beginning < end)
	{
		discompactSimb(tree, discompacted, read_buffer);
		beginning = ftell(compacted);
	}
	
	for(int i = 0; i < 8 - last_byte_bits; ++i)
	{
		discompactSimb(tree, discompacted, read_buffer);
	}

	delete[] alphabet;
	fclose(compacted);
	fclose(discompacted);
}

void HuffmansAlgorithm::discompactSimb(HuffmanTree& t, FILE* f, BufferBitsLeitura& buffer)
{
	uint8_t compacted_bit = buffer.le_bit();
	if (compacted_bit == 0)
	{
		auto flag = t.go_left();
		if (flag)
		{
			fwrite(&(t.getSimb()), 1, 1, f);
			t.resetCurrent();
		}
	}
	else
	{
		auto flag = t.go_right();
		if(flag)
		{
			fwrite(&(t.getSimb()), 1, 1, f);
			t.resetCurrent();
		}
	}
}