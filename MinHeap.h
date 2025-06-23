/********************************************
 *
 * Nathan de Almeida Rezende
 * Luiz Alexandre Espíndola Cunha
 * Erick Rodrigues de Lemos Ribeiro
 * Trabalho de Estrutura de Dados
 * Professor(a): Diego Padilha Rubert
 *
 */

#ifndef __MinHeap_h
#define __MinHeap_h

#include <cstdio>
#include <climits>
#include <string>
#include <vector>
#include <iostream>
#include "FileReader.h"
#include "Node.h"

class Node;
class MinHeap;

class MinHeap
{
	friend class HuffmanTree;
public:
	MinHeap() = default;

	~MinHeap() = default;

	MinHeap(const char*);

	MinHeap(std::vector<Node*>);

	void escreve_niveis() const;

	void escreve(const std::string& prefixo = "", int i = 0) const;

	void insere(Node* p);

	Node* consulta_minimo() const;

	Node* extrai_minimo();


	int size() const
	{
		return _size;
	}

private:
	std::vector<Node*> S;
	int _size{};

	int pai(int i) const;

	int esquerdo(int i) const;

	int direito(int i) const;

	void troca(int i, int j);

	void desce(int i);

	void sobe(int i);
};


//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE HEAP ***
//*************************************

/**Construtor da Min Heap que toma o nome do arquivo. */
MinHeap::MinHeap(const char* fileName) :
	MinHeap(getNodes(fileName))
{
	// do nothing
}

/**Construtor da Min Heap que toma um vetor de nós. */
MinHeap::MinHeap(std::vector<Node*> nodes) :
	S(std::move(nodes))
{
	_size = (int)S.size();
	for (int i = ((int)S.size() / 2) - 1; i >= 0; i--)
		desce(i);
}

/**Função que escreve os níveis da Min Heap (vista como se fosse uma árvore). */
void MinHeap::escreve_niveis() const
{
	int escritos = 0, fim_nivel = 1, sLength = (int)S.size();

	for (int i = 0; i < sLength; i++) {
		S[i]->print();
		if (++escritos == fim_nivel) {
			putchar('\n');
			fim_nivel *= 2;
			escritos = 0;
		}
	}
	putchar('\n');
}

/**Função que escreve a min Heap como uma árvore. */
void MinHeap::escreve(const std::string& prefixo, int i) const
{
	if (i < (int)S.size()) {
		bool ehEsquerdo = i % 2 != 0;
		bool temIrmao = i < (int)S.size() - 1;

		std::cout << prefixo.c_str();
		printf(ehEsquerdo && temIrmao ? "├──" : "└──");

		S[i]->print(" ");

		escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
		escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
	}
}

/**Função que retorna o pai de um nó, dado seu índice no Min Heap. */
int MinHeap::pai(int i) const
{
	return (i - 1) / 2;
}

/**Função que retorna o irmão esquerdo de um nó, dado seu índice no Min Heap. */
int MinHeap::esquerdo(int i) const
{
	return 2 * (i + 1) - 1;
}

/**Função que retorna o irmão direito de um nó, dado seu índice no Min Heap. */
int MinHeap::direito(int i) const
{
	return 2 * (i + 1);
}

/**Função que os índices de dois nós na Min Heap, e então os troca de posição. */
void MinHeap::troca(int i, int j)
{
	Node* aux = S[i];
	S[i] = S[j];
	S[j] = aux;
}

/**Função que desce o nó na Min Heap caso ele seja maior que seus filhos. */
void MinHeap::desce(int i)
{
	int e, d, menor;
	e = esquerdo(i);
	d = direito(i);
	if (e < (int)S.size() && S[e]->key < S[i]->key)
		menor = e;
	else
		menor = i;
	if (d < (int)S.size() && S[d]->key < S[menor]->key)
		menor = d;
	if (menor != i) {
		troca(i, menor);
		desce(menor);
	}
}

/**Função que sobre um nó até que a frequência dele seja maior ou igual a de seu pai. */
void MinHeap::sobe(int i)
{
	while (S[pai(i)]->key > S[i]->key) {
		troca(i, pai(i));
		i = pai(i);
	}
}

/**Função que insere o nó p na Min Heap. */
void MinHeap::insere(Node* p)
{
	S.push_back(p);
	sobe((int)S.size() - 1);
	_size++;
}

/**Função que devolve o nó com a menor frequência. */
Node* MinHeap::consulta_minimo() const
{
	return S[0];
}

/**Função que extrai o nó com a menor frequência. */
Node* MinHeap::extrai_minimo()
{
	Node* menor;
	if (S.size() > 0) {
		menor = S[0]; // ou S.front()
		S[0] = S.back(); // ou S[S.size()-1]
		S.pop_back();
		desce(0);
		_size--;
		return menor;
	}
	else
		return nullptr;
}

#endif // __MinHeap_h