#include <cstdio>
#include <climits>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Node;
class Heap;

class Node
{
    friend class Heap;
public:
    Node();
    Node(int key, char simb);
    ~Node();
    void print(char sep);

private:
    int key;
    char simb;
    Node* lChild;
    Node* rChild;
    Node* parent;
};

class Heap
{
public:
  Heap();
  Heap(int n, Node* dados[]);
  ~Heap();
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(Node* p);
  Node* consulta_maxima();
  Node* extrai_maxima();
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


int main(void)
{

  return 0;
}

/*

Heap h2(5, v);  // o construtor é usado para construir h2
Heap h3(h2);    // o construtor de cópia é usado para construir h3
Heap h4 = h3;   // o construtor de cópia é usado para inicializar um objeto quando há uma atribuição SIMULTÂNEA com a declaração
h = h2;         // o operador de atribuição (cópia) é utilizado (não algum construtor ou transferência)
h = Heap(5, v); // o construtor é usado para construir uma variável temporária, e depois o operação de atribuição (cópia?) é utilizado

** Quando são feitas cópias de objetos **

O C++ chama um construtor de cópia para fazer uma cópia de um objeto
conforme descrito nos casos acima. Se não houver um construtor de
cópias definido para a classe, o C ++ definirá um construtor de cópias
padrão, que copia cada campo (utilizando o construtor de cópia de cada
campo, se for o caso).


** Não escreva um construtor de cópias a menos que necessário **

Se o objeto não tiver ponteiros para a memória alocada dinâmicamente,
uma cópia "superficial" provavelmente será suficiente. Portanto, o
construtor de cópia padrão, o operador de atribuição padrão e o
destruidor padrão estão ok e você não precisa escrever seus próprios.


** Se você precisar de um construtor de cópias, também precisará de um **
** destruidor e um operador de atribuição (operator=) **

Se você precisa de um construtor de cópias, é porque precisa de algo
como uma cópia profunda ou algum outro gerenciamento de
recursos. Assim, é quase certo que você precisará definir um destruidor e
um operador de atribuição.


** Diferença entre construtor de cópia e atribuição **

Um construtor de cópia é usado para inicializar uma variável EM SUA
DECLARAÇÃO a partir de uma variável existente. É parecido com a
atribuição, mas mais simples:

1. Não há necessidade de testar para ver se ele está sendo inicializado por si mesmo
2. Não há necessidade de limpar (por exemplo, excluir) um valor existente (não há nenhum)
3. Uma referência a si mesma não é devolvida.


** Transferência **

Na maioria das vezes, o construtor de transferência ou o operador de
atribuição de trasnferência não são fornecidos pelo compilador. Se
forem, eles farão o mesmo que os construtores/operadores de cópia.

Regra: se você deseja um construtor de transferência e uma atribuição
de transferência que realmente realize a transferência de dados, você
terá que escrevê-los

*/

//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE NODE ***
//*************************************
Node::Node()
{
    key = 0;
    simb = '\0';
    lChild = nullptr;
    rChild = nullptr;
    parent = nullptr;
}

Node::Node(int key, char simb)
{
    this->key = key;
    this->simb = simb;
    lChild = nullptr;
    rChild = nullptr;
    parent = nullptr;
}

Node::~Node()
{
    delete this;
}

void Node::print(char sep)
{
    printf("%d%c", this->key, sep);
}

//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE HEAP ***
//*************************************

Heap::Heap()
{
}

Heap::Heap(int n, Node* dados[]) :
  S(dados, dados + n)
{
    // Starting from the last non-leave element
    for (int i = n/2 - 1; i >= 0; i--)
        desce(i);
}

Heap::~Heap()
{
    for (int i = (int)S.size() - 1; i >= 0; i--)
        delete S[i];
}

void Heap::escreve_niveis()
{
    int escritos = 0, fim_nivel = 1, sLength = S.size();

    for(int i = 0; i < sLength; i++) {
        // Equivalente a for (unsigned i = 0; i < S.size(); i++) { printf("%d ", S[i]);
        S[i]->print(' ');
        if (++escritos == fim_nivel) {
            putchar('\n');
            fim_nivel *= 2;
            escritos = 0;
        }
    }
    putchar('\n');
}

void Heap::escreve(const string& prefixo, int i)
{
  if (i < (int) S.size()) {
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < (int) S.size()-1;

    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" );

    S[i]->print('\n');

    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

int Heap::pai(int i)
{
    return (i - 1) / 2;
}

int Heap::esquerdo(int i)
{
    return 2 * (i + 1) - 1;
}

int Heap::direito(int i)
{
    return 2 * (i + 1);
}

void Heap::troca(int i, int j)
{
    Node* aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

void Heap::desce(int i)
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

void Heap::sobe(int i)
{
    while (S[pai(i)]->key > S[i]->key) {
        troca(i, pai(i));
        i = pai(i);
    }
}

void Heap::insere(Node* p)
{
    S.push_back(p);
    sobe(S.size()-1);
}

Node* Heap::consulta_maxima()
{
    return S[0];
}

Node* Heap::extrai_maxima()
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

void Heap::altera_prioridade(int i, Node* p)
{
    Node* antiga = S[i];
    S[i] = p;
    if (p->key > antiga->key)
        desce(i);
    else
        sobe(i);
    delete antiga;
}
