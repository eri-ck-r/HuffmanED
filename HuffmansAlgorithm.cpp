#include <fstream>
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

    uint16_t alphabet_size = table.leaves.size();
    uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&alphabet_size);
    
    //Criar arquivo compactado
    FILE* compacted = fopen(argv[3], "wb");
    fwrite(&bytePtr[1], 1, 1, compacted);
    fwrite(&bytePtr[0], 1, 1, compacted);
    fseek(compacted, 1, SEEK_CUR); // Pula o 3° byte do arquivo (n° de bits do byte final)

    char* alphabet = table.leaves.data();

    fwrite(alphabet, sizeof(char), alphabet_size, compacted);

    // A partir daqui tem que escrever bit a bit (usar BufferBits)
    BufferBitsEscrita write_buffer(compacted);

    for(int i = 0, size = table.treeCode.size(); i < size; ++i) // Adiciona os bits do percurso em ordem na árvore de Huffman
    {
        uint8_t bit = table.treeCode[i] << size-i;
        write_buffer.escreve_bit(bit); 
    }

    // Compactação em si do "texto" original
    FILE* original = fopen(argv[2], "rb");
    while(!feof(original))
    {
        uint8_t original_byte, compacted_byte;

        fread(&original_byte, 1, 1, original);
        
    }

    fclose(compacted);
}

void HuffmansAlgorithm::discompact(char* argv[])
{

}