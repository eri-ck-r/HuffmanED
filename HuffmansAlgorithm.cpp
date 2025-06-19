#include <fstream>
#include <iostream>
#include "FileReader.h"
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "HuffmanTable.h"
#include "BufferBits.h"

class HuffmansAlgorithm
{
public:
    static void compact(char* argv[]);
    static void discompact(char* argv[]);
};

int main(int argc, char* argv[])
{
    if(argv[1][0] == 'c')
    {
        HuffmansAlgorithm::compact(argv);
    }
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
    
    if(DEBUG_BITS)
    {
        for(size_t i  = 0; i < table.codes.size(); i++)
        {
            printf("%c ", (char)i);
            for(size_t j = 0; j < table.codes[i].size(); j++)
            printf("%u ", table.codes[i][j]);
            printf("\n");
        }
    }

    uint16_t alphabet_size = table.leaves.size();

    // Cria arquivo compactado
    FILE* compacted = fopen(argv[3], "wb");
    fwrite(&alphabet_size, 2, 1, compacted);
    fseek(compacted, 1, SEEK_CUR); // Pula o 3° byte do arquivo (n° de bits do byte final)

    auto alphabet = table.leaves.data();
    fwrite(alphabet, sizeof(alphabet[0]), alphabet_size, compacted);
    
    // A partir daqui tem que escrever bit a bit (usar BufferBits)
    BufferBitsEscrita write_buffer(compacted);
    
    for(int i = 0, size = table.treeCode.size(); i < size; ++i) // Adiciona os bits do percurso em ordem da árvore de Huffman
        write_buffer.escreve_bit(table.treeCode[i]);

    // Compactação em si do "texto" original
    FILE* original = fopen(argv[2], "rb");
    uint8_t original_byte;
    while(fread(&original_byte, 1, 1, original) == 1)
    {
        std::vector<unsigned> simb_code(table.codes[original_byte]);
        
        if(DEBUG_BITS)
        {
            printf("Escrevendo %c ", original_byte);
            for (auto i : simb_code)
                std::cout << i;
            putchar('\n');
        }
        
        for(auto bit : simb_code) // Compacta o byte original
            write_buffer.escreve_bit(bit);
    }
    uint8_t last_byte_bits = write_buffer.livres(); // Guarda os bits de sobra do último byte

    write_buffer.descarrega(); // Escreve o último byte

    fseek(compacted, 2, SEEK_SET);
    fwrite(&last_byte_bits, 1, 1, compacted);

    fclose(compacted);
    fclose(original);
}

void HuffmansAlgorithm::discompact(char* argv[])
{
    
}