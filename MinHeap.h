#include <cstdio>
#include <climits>
#include <string>
#include <vector>
#include "FileReader.h"
#define and &&
#define or ||


using std::string;
using std::vector;

class Node;
class MinHeap;

class Node
{
    friend class MinHeap;
    friend class HuffmanTree;
public:
    Node();
    Node(int key, char simb);
    ~Node();
    void print(const char *sep = " ");

private:
    int key;
    char simb;
    Node* parent;
    Node* left;
    Node* right;
};

class MinHeap
{
    friend class HuffmanTree;
public:
  MinHeap();
  MinHeap(std::vector<Node*> data);
  MinHeap(const char* fileName);
  ~MinHeap();
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(Node* p);
  Node* consulta_minimo();
  Node* extrai_minimo();
  void altera_prioridade(int i, Node* p);


private:
  vector<Node*> S;

  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};


//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE NODE ***
//*************************************
Node::Node() :
  key(0),
  simb('\0'),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
  {}

Node::Node(int key, char simb) :
  key(key),
  simb(simb),
  parent(nullptr),
  left(nullptr),
  right(nullptr)
  {}

Node::~Node()
{
    delete this;
}

void Node::print(const char *sep)
{
    printf("%d%s", key, sep);
}

//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE HEAP ***
//*************************************

MinHeap::MinHeap()
{
}

MinHeap::MinHeap(vector<Node*> nodes) :
  S(nodes)
{
    // Starting from the last non-leave element
    for (int i = (int)(nodes.size())/2 - 1; i >= 0; i--)
        desce(i);
}

MinHeap::MinHeap(const char *fileName):
    S(std::move(getNodes(fileName)))
{
    for(int i = S.size()/2 - 1; i >=0; i--)
    {
        
    }
}

MinHeap::~MinHeap()
{
    for (int i = (int)S.size() - 1; i >= 0; i--)
        delete S[i];
}

void MinHeap::escreve_niveis()
{
    int escritos = 0, fim_nivel = 1, sLength = S.size();

    for(int i = 0; i < sLength; i++) {
        // Equivalente a for (unsigned i = 0; i < S.size(); i++) { printf("%d ", S[i]);
        S[i]->print();
        if (++escritos == fim_nivel) {
            putchar('\n');
            fim_nivel *= 2;
            escritos = 0;
        }
    }
    putchar('\n');
}

void MinHeap::escreve(const string& prefixo, int i)
{
  if (i < (int) S.size()) {
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < (int) S.size()-1;

    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" );

    S[i]->print("\n");

    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

int MinHeap::pai(int i)
{
    return (i - 1) / 2;
}

int MinHeap::esquerdo(int i)
{
    return 2 * (i + 1) - 1;
}

int MinHeap::direito(int i)
{
    return 2 * (i + 1);
}

void MinHeap::troca(int i, int j)
{
    Node* aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

void MinHeap::desce(int i)
{
    int e, d, menor;
    e = esquerdo(i);
    d = direito(i);
    if (e < (int) S.size() && S[e]->key < S[i]->key)
        menor = e;
    else
        menor = i;
    if (d < (int) S.size() && S[d]->key < S[menor]->key)
        menor = d;
    if (menor != i) {
        troca(i, menor);
        desce(menor);
    }
}

void MinHeap::sobe(int i)
{
    while (S[pai(i)]->key > S[i]->key) {
        troca(i, pai(i));
        i = pai(i);
    }
}

void MinHeap::insere(Node* p)
{
    S.push_back(p);
    sobe(S.size()-1);
}

Node* MinHeap::consulta_minimo()
{
    return S[0];
}

Node* MinHeap::extrai_minimo()
{
    Node* menor;
    if (S.size() > 0) {
        menor = S[0]; // ou S.front()
        S[0] = S.back(); // ou S[S.size()-1]
        S.pop_back();
        desce(0);
        return menor;
    }
    else
        return nullptr;
}

void MinHeap::altera_prioridade(int i, Node* p)
{
    Node* antiga = S[i];
    S[i] = p;
    if (p->key > antiga->key)
        desce(i);
    else
        sobe(i);
    delete antiga;
}
