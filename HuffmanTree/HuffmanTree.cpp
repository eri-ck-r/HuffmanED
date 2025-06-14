#include <cstdio>
#include <string>

using std::string;

class Node
{
  friend class ArvBinBusca;

public:
    Node();
    Node(int key, char simb);
    ~Node();
    void print(const char* sep = "");

private:
    int key;
    char simb;
    Node* parent;
    Node* left;
    Node* right;
};


class ArvBinBusca
{
public:
  ArvBinBusca();
  ArvBinBusca(const ArvBinBusca& outro); // construtor de cópia
  ~ArvBinBusca();
  ArvBinBusca& operator=(const ArvBinBusca& outro); // operador de atribuição

  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();

  Node* get_raiz(); // devolve a raiz
  Node* busca(int k); // devolve o ponteiro para um elemento, se achar, ou NULL
  Node* minimo(); // devolve o menor elemento da árvore
  Node* maximo(); // devolve o maior elemento da árvore
  Node* sucessor(Node* x); // devolve o sucessor de um elemento
  Node* predecessor(Node* x); // devolve o predecessor de um elemento

  void insere(int chave);
  bool remove(int chave);

  void limpa(); // remove todos elementos da árvore

private:
  Node* raiz;

  void escreve_ordenado(Node* x); // escreve em percurso em-ordem
  void escreve(const string& prefixo, Node* x);

  Node* busca(Node* x, int k);
  Node* minimo(Node* x);
  Node* maximo(Node* x);

  void insere(Node* z);
  void transplante(Node* u, Node* v);
  void remove(Node* z);

  void limpa(Node* x); // dado um nó x, remove recursivamente elementos abaixo e deleta x

  void copia(const ArvBinBusca& T); // copia uma árvore T para a atual a partir da raiz,
                                    // usada no construtor de cópia e no operador de atribuição
  void copia(Node* dest, Node* orig);   // copia um nó e os descendentes recursivamente
};


int main(void)
{

  return 0;
}


//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE NODE ***
//***********************************
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


//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE ARVBINBUSCA ***
//********************************************

ArvBinBusca::ArvBinBusca()
{
  raiz = nullptr;
}

ArvBinBusca::ArvBinBusca(const ArvBinBusca& outro)
{
  copia(outro);
}

ArvBinBusca::~ArvBinBusca()
{
  limpa();
}

ArvBinBusca& ArvBinBusca::operator=(const ArvBinBusca& outro)
{
  limpa();
  copia(outro);
  return *this;
}

void ArvBinBusca::escreve_ordenado()
{
  escreve_ordenado(raiz);
  putchar('\n');
}

void ArvBinBusca::escreve_ordenado(Node* x)
{
  //TODO: implementar (escrever em percurso em-ordem em uma única linha)
}

void ArvBinBusca::escreve()
{
  escreve("", raiz);
}

void ArvBinBusca::escreve(const string& prefixo, No *x)
{
  if (x == nullptr)
    return;

  bool ehDireito = x->pai and x->pai->dir == x;
  bool temIrmaoEsq = x->pai and x->pai->esq;

  printf(prefixo.c_str());
  printf(ehDireito and temIrmaoEsq ? "├──" : "└──" );

  if (x->pai == nullptr) // raiz
    x->escreve("\n");
  else
    x->escreve(ehDireito ? "d\n" : "e\n");

  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->dir);
  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->esq);
}

Node* ArvBinBusca::get_raiz()
{
  return raiz;
}

void ArvBinBusca::limpa()
{
  limpa(raiz);
  raiz = nullptr;
}

void ArvBinBusca::limpa(Node* x)
{
  //TODO: implementar
}

void ArvBinBusca::copia(const ArvBinBusca& T)
{
  if (T.raiz == nullptr)
    raiz = nullptr;
  else {
    raiz = new Node(T.raiz->chave);
    copia(raiz, T.raiz);
  }
}

void ArvBinBusca::copia(Node* dest, Node* orig)
{
  //TODO: implementar
}
