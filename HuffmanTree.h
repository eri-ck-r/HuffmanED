#ifndef __HuffmanTree_h
#define __HuffmanTree_h
#include <cstdio>
#include <string>
#include <vector>
#include "MinHeap.h"
#include "FileReader.h"
#include "Node.h"

class HuffmanTree
{
  friend class HuffmanTable;
public: 
  HuffmanTree();
  HuffmanTree(MinHeap& h);
  HuffmanTree(std::vector<unsigned> treeCode, std::vector<char> leaves);
  ~HuffmanTree();

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();

  Node* get_raiz(); // devolve a raiz
  int get_leaves(); // devolve nLeaves
 
  void limpa(); // remove todos elementos da árvore

private:
  Node* root;
  int nLeaves;

  void build(unsigned* i, char* s, Node* x);
  void escreve_ordenado(Node* x); // escreve em percurso em-ordem
  void escreve(const std::string& prefixo, Node* x);

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

/**Constructor which takes a coded Huffman tree and the simbols
 */
HuffmanTree::HuffmanTree(std::vector<unsigned> treeCode, std::vector<char> leaves):
nLeaves((int)leaves.size())
{
  if ((int)treeCode.size() > 0){
    unsigned* i = treeCode.data();
    char* s = leaves.data();
    root = new Node();
    build(i, s, root); // at first, the node* received its the root
  }
  else 
    root = nullptr;
}

HuffmanTree::~HuffmanTree()
{
  limpa();
}

void HuffmanTree::build(unsigned* i, char* s, Node* x)
{
  if (x == nullptr)
    return;
  else{
    // if x is a branch
    if ((*i) == 0){
        Node* l = new Node();
        Node* r = new Node();
        x->left = l;
        x->right = r;
        r->parent = l->parent = x;

      build(++i, s, x->left);
      build(++i, s, x->right);
    }
    else{
      //its a leave
      x->simb = (*s);
      s++;
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

void HuffmanTree::escreve(const std::string& prefixo, Node* x)
{
  if (x == nullptr)
    return;

  bool ehDireito = (x->parent && x->parent->right == x);
  bool temIrmaoEsq = x->parent && x->parent->left;

  printf(prefixo.c_str());
  printf(ehDireito && temIrmaoEsq ? "├──" : "└──" );

  if (x->parent == nullptr) // raiz
    x->print("\n");
  else
    x->print(ehDireito ? "d\n" : "e\n");

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
  else{
    limpa(x->left);
    limpa(x->right);
    delete x;
  }
}

#endif // __HuffmanTree_h