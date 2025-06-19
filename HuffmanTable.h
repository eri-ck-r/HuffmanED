#ifndef __HuffmanTable_h
#define __HuffmanTable_h
#include <cstdio>
#include <string>
#include <vector>
#include "FileReader.h"
#include "MinHeap.h"
#include "HuffmanTree.h"

class HuffmanTable
{
	friend class HuffmansAlgorithm;

public:
	HuffmanTable(const HuffmanTree& T);
	HuffmanTable(const char* fileName);
private:
	std::vector<std::vector<bool>> codes;
	std::vector<bool> stack;
	std::vector<bool> treeCode;
	std::vector<char> leaves;  // Símbolos pré-ordem da árvore de Huffman
	void build(Node* x);
};

//*********************************************
//*** IMPLEMENTAÇÕES DA CLASSE HuffmanTable ***
//*********************************************

HuffmanTable::HuffmanTable(const HuffmanTree& T) :
	codes(256),
	stack(0),
	treeCode(0),
	leaves(0)
{
	build(T.root);
}

void HuffmanTable::build(Node* x)
{
	if (x == nullptr)
		return;
	
	if (x->left != nullptr || x->right != nullptr)
		treeCode.push_back(0); // puts the encoding 0 for a branch
	else
	{
		// its a leave
		treeCode.push_back(1); // puts the encoding 1 for a leave
		codes[(unsigned)x->simb] = std::vector<bool>(stack);
		leaves.push_back(x->simb);
	}

	stack.push_back(0);
	build(x->left);
	stack.pop_back();

	stack.push_back(1);
	build(x->right);
	stack.pop_back();

}
#endif // __HuffmanTable_h