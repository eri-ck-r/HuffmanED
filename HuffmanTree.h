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
<<<<<<< HEAD
	friend class HuffmanTable;
public:
	HuffmanTree();
	HuffmanTree(MinHeap& h);
	HuffmanTree(std::vector<unsigned> treeCode, std::vector<char> leaves);
	~HuffmanTree();

	void escreve_ordenado(); // escreve em percurso em-ordem
	void escreve();
=======
  friend class HuffmanTable;
public: 
  HuffmanTree() = default;
  HuffmanTree(MinHeap& h);
  HuffmanTree(std::vector<unsigned> treeCode, std::vector<char> leaves);
  ~HuffmanTree();

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();
  void escreve_bfs();
>>>>>>> f651c590f9a189a2937be058f128cd9d12f3718d

	Node* get_raiz(); // devolve a raiz
	int get_leaves(); // devolve nLeaves

	void limpa(); // remove todos elementos da árvore

private:
<<<<<<< HEAD
	Node* root;
	int nLeaves;

	void build(unsigned* i, char* s, Node* x);
	void escreve_ordenado(Node* x); // escreve em percurso em-ordem
	void escreve(const std::string& prefixo, Node* x);
=======
    Node* root{};
    int nLeaves{};

  void decode(unsigned* i, char* s, Node* x);
  void escreve_ordenado(Node* x); // escreve em percurso em-ordem
  void escreve(const std::string& prefixo, Node* x);
>>>>>>> f651c590f9a189a2937be058f128cd9d12f3718d

	void limpa(Node* x); // dado um nó x, remove recursivamente elementos abaixo e deleta x

};


//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE HUFFMANTREE ***
//********************************************

<<<<<<< HEAD
HuffmanTree::HuffmanTree()
{
	root = nullptr;
}

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
=======


HuffmanTree::HuffmanTree(MinHeap& h):
    nLeaves(h.size())
{
  while((int)h.S.size() > 1){
    Node* n = new Node(0,'0');
    n->left = h.extrai_minimo();
    n->right = h.extrai_minimo();
    n->key = n->left->key + n->right->key;
    h.insere(n);
  }
  root = h.extrai_minimo();
>>>>>>> f651c590f9a189a2937be058f128cd9d12f3718d
}

/**Constructor which takes a coded Huffman tree and the simbols
 */
HuffmanTree::HuffmanTree(std::vector<unsigned> treeCode, std::vector<char> leaves) :
	nLeaves((int)leaves.size())
{
<<<<<<< HEAD
	if ((int)treeCode.size() > 0) {
		unsigned* i = treeCode.data();
		char* s = leaves.data();
		root = new Node();
		build(i, s, root); // at first, the node* received its the root
	}
	else
		root = nullptr;
=======
  if ((int)treeCode.size() > 0){
    unsigned* i = treeCode.data();
    char* s = leaves.data();
    root = new Node();
    decode(i, s, root); // at first, the node* received its the root
  }
  else 
    root = nullptr;
>>>>>>> f651c590f9a189a2937be058f128cd9d12f3718d
}

HuffmanTree::~HuffmanTree()
{
	limpa();
}

void HuffmanTree::decode(unsigned* i, char* s, Node* x)
{
	if (x == nullptr)
		return;
	else {
		// if x is a branch
		if ((*i) == 0) {
			Node* l = new Node();
			Node* r = new Node();
			x->left = l;
			x->right = r;
			r->parent = l->parent = x;

<<<<<<< HEAD
			build(++i, s, x->left);
			build(++i, s, x->right);
		}
		else {
			//its a leave
			x->simb = (*s);
			s++;
		}
	}
=======
      decode(++i, s, x->left);
      decode(++i, s, x->right);
    }
    else{
      //its a leave
      x->simb = (*s);
      s++;
    }
  }
>>>>>>> f651c590f9a189a2937be058f128cd9d12f3718d
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
	else {
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

<<<<<<< HEAD
	if (x->parent == nullptr) // raiz
		x->print("\n");
	else
		x->print(ehDireito ? "d\n" : "e\n");
=======
  if (x->parent == nullptr) // raiz
    x->print(" ");
  else
    x->print(ehDireito ? "d " : "e ");
>>>>>>> f651c590f9a189a2937be058f128cd9d12f3718d

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

void HuffmanTree::limpa()
{
	limpa(root);
	root = nullptr;
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

#endif // __HuffmanTree_h