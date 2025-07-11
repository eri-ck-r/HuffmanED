#ifndef __HuffmanTree_h
#define __HuffmanTree_h
#include <cstdio>
#include <queue>
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

  Node* get_raiz(); // devolve a raiz
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

/**Constructor which takes a coded Huffman tree and the simbols
 */
HuffmanTree::HuffmanTree(std::vector<bool> treeCode, std::vector<unsigned char>& leaves) :
	nLeaves((int)leaves.size())
{
	if ((int)treeCode.size() > 0) {
		int i = 0;
		unsigned char* r = leaves.data();
		root = new Node();
		current = root;
		decode(i, &r, root, treeCode); // at first, the node* received its the root
	}
	else
		root = nullptr;
}

HuffmanTree::~HuffmanTree()
{
	limpa();
}

void HuffmanTree::decode(int& i, unsigned char** s, Node* x, std::vector<bool>& treeCode)
{
	if (x == nullptr)
		return;
	else
	{
		// if x is a branch
		std::cout << "valor de i  = " << treeCode[i] << std::endl;
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
			//its a leave
			x->simb = (**s);
			(*s)++;
		}
	}
}

void HuffmanTree::escreve_ordenado()
{
	escreve_ordenado(root);
	putchar('\n');
}

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

void HuffmanTree::escreve()
{
	escreve("", root);
}

void HuffmanTree::escreve_bfs()
{
    if (root == nullptr)
        return;
    std::queue<Node*> q;
    q.push(root);
    
    while (!q.empty())
    {
        Node* currentNode = q.front();
        q.pop();
        currentNode->print();

        if (currentNode->left)
            q.push(currentNode->left);
        if (currentNode->right)
            q.push(currentNode->right);
    }
}

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

Node* HuffmanTree::get_raiz()
{
	return root;
}

int HuffmanTree::get_leaves()
{
	return nLeaves;
}

bool HuffmanTree::go_left()
{
	current = current->left;
	return current->isLeaf();
}

bool HuffmanTree::go_right()
{
	current = current->right;
	return current->isLeaf();
}

void HuffmanTree::limpa()
{
	limpa(root);
	root = nullptr;
	current = nullptr;
}

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
/*
		!
	!		A
  F   ! 
    S   D


*/
#endif // __HuffmanTree_h