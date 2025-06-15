#include <fstream>
#include "FileReader.h"
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "pilha.h"
 
int main(int argc, char* argv[])
{
    //HuffmanTree tree{"nome do arquivo"};

    // Compactar
    if(argv[1][0] == 'c')
    {
        
        auto nodes = getNodes(argv[2]);
        MinHeap mh(nodes);
        
        HuffmanTree tree(mh);

        uint16_t alphabet = tree.nLeaves;

          //Montar cabeçalho
        uint8_t* bytePtr = reinterpret_cast<char*>(&alphabet);

        //Criar arquivo compactado
        std::ifstream reader(fileName);
    }
    // Descompactar
    else  // if(argv[1][0] == 'd')
    {
        
    }
}