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
        
        auto v = getNodes(argv[2]);
        MinHeap mh(v);
        
        HuffmanTree tree(mh);

        
    }
    // Descompactar
    else  // if(argv[1][0] == 'd')
    {
        
    }
}