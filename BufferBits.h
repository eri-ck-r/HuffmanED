#ifndef __BufferBits_h
#define __BufferBits_h
#include <cstdio>
#include <cstdint>


// Buffer de 1 byte para leitura ou escrita bit-a-bit em arquivo (classe base).
class BufferBits {
protected:
	FILE* arquivo;  // Ponteiro para o arquivo sendo lido/escrito
	uint8_t byte;   // Buffer com bits de um byte
	uint8_t n;      /** Quantidade de bits que ainda tem para devolver (leitura) / quantos já escreveu (escrita) */

public:
	BufferBits(FILE* arquivo);  // Construtor padrão com o arquivo que será lido ou escrito
	uint8_t ocupados();         // Devolve quantos bits estão ocupados no buffer
	uint8_t livres();           // Devolve quantos bits ainda podem ser adicionados ao buffer do byte
};

// Buffer de leitura de bits
class BufferBitsLeitura : public BufferBits {
public:
	BufferBitsLeitura(FILE* arquivo); // Construtor padrão com o arquivo que será lido
	uint8_t le_bit();                 // Lê o próximo bit do buffer (lê um byte do arquivo se estiver vazio)
};

// Buffer de escrita de bits
class BufferBitsEscrita : public BufferBits {
public:
	BufferBitsEscrita(FILE* arquivo);  // Construtor padrão com o arquivo que será escrito
	void escreve_bit(uint8_t bit);     // Escreve um bit 0 ou 1 no buffer (escreve byte no arquivo se completar 8 bits)
	void descarrega();                 // Força a escrita do byte no buffer (completa com 0s, caso necessário)
};


int DEBUG_BITS = 0;


void escrever_binario(uint8_t numero)
{
	for (int i = 128; i > 0; i >>= 1)
		printf("%c", numero & i ? '1' : '0');
}

BufferBits::BufferBits(FILE* arquivo) :
	arquivo(arquivo),
	byte(0),
	n(0)
{
}

uint8_t BufferBits::ocupados()
{
	return n;
}

uint8_t BufferBits::livres()
{
	return 8 - n;
}

BufferBitsLeitura::BufferBitsLeitura(FILE* f) :
	BufferBits(f)
{
}

uint8_t BufferBitsLeitura::le_bit()
{
	// Caso n == 0, lê 1 byte do arquivo e colocar no buffer
	// Se não houver mais bytes para serem lidos do arquivo, devolve o valor 2
	if (n == 0)
	{
		if (fread(&this->byte, 1, 1, this->arquivo) == 0)
			return 3;
		n = 8;
	}

	if (DEBUG_BITS)
	{
		printf("n: %d, byte: %d (", n, byte);
		escrever_binario(byte);
	}

	// Coloca em bit o próximo bit, e decrementa n
	uint8_t bit;
	bit = this->byte & (1 << (n - 1));
	n--;

	if (DEBUG_BITS)
	{
		printf(") --> %d(", byte);
		escrever_binario(byte);
		printf("), bit: %d\n", bit);
	}

	return bit;
}

BufferBitsEscrita::BufferBitsEscrita(FILE* f) :
	BufferBits(f)
{
}

void BufferBitsEscrita::escreve_bit(uint8_t bit)
{
	if (DEBUG_BITS)
	{
		printf("bit: %d, n: %d, byte: %d (", bit, n, byte);
		escrever_binario(byte);
	}


	// Adiciona o bit ao byte na posição correta
	this->byte |= bit << (7 - n);
	n++;

	if (DEBUG_BITS)
	{
		printf(") --> %d(", byte);
		escrever_binario(byte);
		printf(")\n");
	}
	if (n == 8)
		descarrega();
}

void BufferBitsEscrita::descarrega()
{
	fwrite(&byte, 1, 1, arquivo);

	if (DEBUG_BITS)
	{
		printf("!!!!!!! byte escrito = ");
		escrever_binario(byte);
		printf("\n\n");
	}

	n = 0;
	byte = 0;
}

#endif // __BufferBits_h