#include <cstdio>
#include <string>
#include <vector>
#include "FileReader.h"
#include "MinHeap.h"
#include "HuffmanTree.h"

#define and &&
#define or ||

using std::string;
using std::vector;

class HuffmanTable
{
    public:
        HuffmanTable(const HuffmanTree& T);
        HuffmanTable(const char* fileName);
    private:
        vector<vector<unsigned>> codes;
        vector<unsigned> stack;
        vector<unsigned> treeCode;
        vector<char> leaves;  // Símbolos pré-ordem da árvore de Huffman
        void build(Node* x);
};

//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE HuffmanTable ***
//*************************************

HuffmanTable::HuffmanTable(const HuffmanTree& T) :
codes(256),
stack(256),
treeCode(256),
leaves(T.nLeaves)
{
    build(T.root);
}

void HuffmanTable::build(Node* x)
{
    if (x == nullptr)
        return nullptr;
    else{
        // its a branch
        if (x->left != nullptr or x->right != nullptr){
            treeCode.push_back(0); // puts the encoding 0 for a branch
        }
        else{
            // its a leave
            treeCode.push_back(1); // puts the encoding 1 for a leave
            codes[(int)x->simb] = std::vector<unsigned>(stack);
            leaves.push_back(x->simb);
        }
        stack.push_back(0);
        build(x->left);
        stack.pop_back();
        
        stack.push_back(1);
        build(x->right);
        stack.pop_back();
    }
}