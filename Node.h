/********************************************
 *
 * Nathan de Almeida Rezende
 * Luiz Alexandre Espíndola Cunha
 * Trabalho de Estrutura de Dados
 * Professor(a): Diego Padilha Rubert
 *
 */

#ifndef __Node_h
#define __Node_h

class MinHeap;
class HuffmanTree;
class HuffmanTable;

class Node
{
public:
	friend class MinHeap;
	friend class HuffmanTree;
	friend class HuffmanTable;

	Node() = default;

	Node(int key, unsigned char simb);

	~Node() = default;

	void print(const char* sep = " ") const;

	bool isLeaf()
	{
		return left == nullptr && right == nullptr;
	}

private:
	int key{};
	unsigned char simb{};
	Node* parent{};
	Node* left{};
	Node* right{};
};

//*************************************
//*** IMPLEMENTA��ES DA CLASSE NODE ***
//*************************************


Node::Node(int key, unsigned char simb) :
	key(key),
	simb(simb)
{
	//do nothing
}

void Node::print(const char* sep) const
{
	std::cout << "freq: " << key << sep << "char: " << simb << std::endl;
}

#endif // __Node_h


