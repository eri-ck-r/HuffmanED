/********************************************
 *
 * Nathan de Almeida Rezende
 * Luiz Alexandre Espíndola Cunha
 * Erick Rodrigues de Lemos Ribeiro
 * Trabalho de Estrutura de Dados
 * Professor(a): Diego Padilha Rubert
 *
 */

#ifndef __HuffmanTree_h
#define __HuffmanTree_h
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include "MinHeap.h"
#include "FileReader.h"
#include "Node.h"

class HuffmanTree
{
  friend class HuffmanTable;
public: 
  HuffmanTree() = default;
  HuffmanTree(MinHeap& h);
  HuffmanTree(std::vector<bool> treeCode, std::vector<unsigned char>& leaves);
  ~HuffmanTree();

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();
  void escreve_bfs();

  int get_leaves(); // devolve nLeaves
  bool go_left();
  bool go_right();
  void resetCurrent()
  {
	current = root;
  }

  unsigned char& getSimb()
  {
	return current->simb;
  }
  
  void limpa(); // remove todos elementos da árvore

private:
	Node* root{};
	Node* current{};
	int nLeaves{};

	void decode(int& i, unsigned char** s, Node* x, std::vector<bool>& treeCode);
	void escreve_ordenado(Node* x); // escreve em percurso em-ordem
	void escreve(const std::string& prefixo, Node* x);

	void limpa(Node* x); // dado um nó x, remove recursivamente elementos abaixo e deleta x

};


//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE HUFFMANTREE ***
//********************************************

/**Construtor que, tomado uma Min Heap h, constrói a árvore de Huffman. */
HuffmanTree::HuffmanTree(MinHeap& h) :
	nLeaves((int)h.S.size())
{
	while ((int)h.S.size() > 1) {

		Node* n = new Node(0, '0');
		n->left = h.extrai_minimo();
		n->right = h.extrai_minimo();
		n->key = n->left->key + n->right->key;
		h.insere(n);
	}
	root = h.extrai_minimo();
	current = root;
}

/**Construtor que toma um vector com a codificação da árvore de Huffman
 * e com as folhas dela, no percurso pré-ordem, e então constrói a árvore
 * para decodificação.
 */
HuffmanTree::HuffmanTree(std::vector<bool> treeCode, std::vector<unsigned char>& leaves) :
	nLeaves((int)leaves.size())
{
	if ((int)treeCode.size() > 0) {
		int i = 0;
		unsigned char* r = leaves.data();
		root = new Node();
		current = root;
		decode(i, &r, root, treeCode); 
	}
	else
		root = nullptr;
}

/**Destrutor da árvore de Huffman. */
HuffmanTree::~HuffmanTree()
{
	limpa();
}

/**Função que decodifica o código recebido da árvore e a constrói recursivamente,
 * tomados um índice para a posição atual no vetor da árvore, um ponteiro para o ponteiro
 * que indica a posição atual no vetor das folhas, o nó atual, e o vetor da codificação da árvore.
 */
void HuffmanTree::decode(int& i, unsigned char** s, Node* x, std::vector<bool>& treeCode)
{
	if (x == nullptr)
		return;
	else
	{
		// se é um ramo
		if (treeCode[i] == 0)
		{
			x->simb = '!';
			Node* l = new Node();
			Node* r = new Node();
			x->left = l;
			x->right = r;
			r->parent = l->parent = x;
			// i = 0
			decode(++i, s, x->left, treeCode);
			// i = 1 
			decode(++i, s, x->right, treeCode);
			// i = 2
		}
		else
		{
			// se é uma folha
			x->simb = (**s);
			(*s)++;
		}
	}
}

/**Função que escreve a árvore ordenada. */
void HuffmanTree::escreve_ordenado()
{
	escreve_ordenado(root);
	putchar('\n');
}

/**Função que escreve a árvore ordenada, considerando um percurso em-ordem. */
void HuffmanTree::escreve_ordenado(Node* x)
{
	if (x == nullptr)
		return;
	else
	{
		escreve_ordenado(x->left);
		x->print();
		escreve_ordenado(x->right);
	}
}

/**Função que escreve a árvore. */
void HuffmanTree::escreve()
{
	escreve("", root);
}

/**Função que escreve a árvore tomado um prefixo e o nó atual. */
void HuffmanTree::escreve(const std::string& prefixo, Node* x)
{
	if (x == nullptr)
		return;

	bool ehDireito = (x->parent && x->parent->right == x);
	bool temIrmaoEsq = x->parent && x->parent->left;

	std::cout << prefixo.c_str();
	printf(ehDireito && temIrmaoEsq ? "├──" : "└──");

	if (x->parent == nullptr) // raiz
		x->print("");
	else
		x->print(ehDireito ? "d" : "e");

	escreve(prefixo + (ehDireito && temIrmaoEsq ? "│   " : "    "), x->right);
	escreve(prefixo + (ehDireito && temIrmaoEsq ? "│   " : "    "), x->left);
}

/**Função que retorna o número de folhas. */
int HuffmanTree::get_leaves()
{
	return nLeaves;
}

/**Função que move o nó atual para esquerda e retorna true se é folha, ou false caso
 * contrário.
 */
bool HuffmanTree::go_left()
{
	current = current->left;
	return current->isLeaf();
}

/**Função que move o nó atual para direita e retorna true se é folha, ou false caso
 * contrário.
 */
bool HuffmanTree::go_right()
{
	current = current->right;
	return current->isLeaf();
}

/**Função que destrói a árvore. */
void HuffmanTree::limpa()
{
	limpa(root);
	root = nullptr;
	current = nullptr;
}

/**Função que deleta os nós na árvore em pós-ordem. */
void HuffmanTree::limpa(Node* x)
{
	if (x == nullptr)
		return;
	else {
		limpa(x->left);
		limpa(x->right);
		delete x;
	}
}

#endif // __HuffmanTree_h