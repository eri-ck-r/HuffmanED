#include <cstdio>
#include <string>
#include "MinHeap.h"
#include "FileReader.h"

#define and &&
#define or ||

using std::string;


class HuffmanTree
{
  friend class HuffmanTable;
public: 
  HuffmanTree();
  HuffmanTree(MinHeap& h);
  ~HuffmanTree();

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();

  Node* get_raiz(); // devolve a raiz
  int get_leaves(); // devolve nLeaves
 
  void limpa(); // remove todos elementos da árvore

private:
  Node* root;
  int nLeaves;

  void escreve_ordenado(Node* x); // escreve em percurso em-ordem
  void escreve(const string& prefixo, Node* x);

  void limpa(Node* x); // dado um nó x, remove recursivamente elementos abaixo e deleta x

};


//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE HUFFMANTREE ***
//********************************************

HuffmanTree::HuffmanTree()
{
  root = nullptr;
}

HuffmanTree::HuffmanTree(MinHeap& h):
nLeaves((int)h.S.size())
{
  while((int)h.S.size() > 1){
    Node* n = new Node();
    n->left = h.extrai_minimo();
    n->right = h.extrai_minimo();
    n->key = n->left->key + n->right->key;
    h.insere(n);
  }
  h.extrai_minimo();
}

HuffmanTree::~HuffmanTree()
{
  limpa();
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
  else{
    escreve_ordenado(x->left);
    x->print();
    escreve_ordenado(x->right);
  }
}

void HuffmanTree::escreve()
{
  escreve("", root);
}

void HuffmanTree::escreve(const string& prefixo, Node* x)
{
  if (x == nullptr)
    return;

  bool ehDireito = (x->parent and x->parent->right == x);
  bool temIrmaoEsq = x->parent and x->parent->left;

  printf(prefixo.c_str());
  printf(ehDireito and temIrmaoEsq ? "├──" : "└──" );

  if (x->parent == nullptr) // raiz
    x->print("\n");
  else
    x->print(ehDireito ? "d\n" : "e\n");

  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->right);
  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->left);
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
  raiz = nullptr;
}

void HuffmanTree::limpa(Node* x)
{
  if (x == nullptr)
    return;
  else{
    limpa(x->left);
    limpa(x->right);
    delete x;
  }
}

