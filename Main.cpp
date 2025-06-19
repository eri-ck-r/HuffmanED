#include <cstdio>
#include "FileReader.h"
#include "HuffmanTree.h"
#include "MinHeap.h"
#include "HuffmanTable.h"
#include "BufferBits.h"

using namespace std;

int main(int argc, char *argv[])
{
  FILE *f1 = fopen(argv[1], "rb");
  FILE *f2 = fopen(argv[2], "wb");

  BufferBitsLeitura bl(f1);  // Não usa new, não é Java
  BufferBitsEscrita be(f2);  // Não usa new, não é Java
  while(!feof(f1))
    be.escreve_bit(bl.le_bit());

  fclose(f1);
  fclose(f2);
  return 0;
}