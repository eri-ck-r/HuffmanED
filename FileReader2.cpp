/********************************************
 *
 * Nathan de Almeida Rezende
 * Luiz Alexandre Espíndola Cunha
 * Trabalho de Estrutura de Dados
 * Professor(a): Diego Padilha Rubert
 *
 */
#include <cstdio>
#include <cstdint>


/*
Tarefas:

  1. Calcular a frequencia dos caracteres

  2. Criar min-heap e ir usando-a pra criar a árvore de Huffman

  3. Mapear os códigos em uma tabela

  4. Gerar arquivo compactado em si com o cabeçalho

*/


int main(int argc, char* argv[])
{
    FILE *f = fopen(argv[2], "rb");
    
    // 1
    if(argv[1][0] == 'c')  // Compactar
    {
        int freq[256] = {0};

        uint8_t byte;  // Vai percorrer cada byte de f
        while(!feof(f))
        {
            fread(&byte, 1, 1, f);
            freq[byte]++;
        }
        for(int i = 0; i < 256; ++i)
        printf("%d (%d)\n", freq[i], i);

        // construir vetor de ponteiros para nós
        for()
    }
    else  // if(argv[1][0] == 'd')
    {
        // descompactar
    }

    fclose(f);
    return 0;
}
