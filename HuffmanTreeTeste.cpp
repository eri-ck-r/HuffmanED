#include <iostream>
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "HuffmanTable.h"

int main(int argc, char* argv[])
{
    // initiallizing min heap
    MinHeap mh(argv[1]);
    //mh.escreve();

    // -- tree
    HuffmanTree t(mh);
    t.escreve_ordenado();

    // -- table

    return 0;
}