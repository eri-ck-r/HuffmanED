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

    Node(int key, char simb);

    ~Node() = default;

    void print(const char* sep = " ") const;

private:
    int key{};
    char simb{};
    Node* parent{};
    Node* left{};
    Node* right{};
};

//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE NODE ***
//*************************************


Node::Node(int key, char simb) :
    key(key),
    simb(simb)
{ 
    //do nothing
}

void Node::print(const char* sep) const
{
    std::cout << "key: " << key << sep << "char: " << simb << std::endl;
    //printf("%d%s", key, sep);
}

#endif


