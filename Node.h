#ifndef __Node_h
#define __Node_h
#include <cstdint>

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

	Node(int key, uint8_t simb);

	~Node() = default;

	void print(const char* sep = " ") const;

	bool isLeaf()
	{
		return left == nullptr && right == nullptr;
	}

private:
	int key{};
	uint8_t simb{};
	Node* parent{};
	Node* left{};
	Node* right{};
};

//*************************************
//*** IMPLEMENTA��ES DA CLASSE NODE ***
//*************************************


Node::Node(int key, uint8_t simb) :
	key(key),
	simb(simb)
{
	//do nothing
}

void Node::print(const char* sep) const
{
	std::cout << "freq: " << key << sep << "char: " << simb << std::endl;
	//printf("%d%s", key, sep);
}

#endif // __Node_h


