#include "Huffman.h"
#include <sstream>

void Huffman::treeParse(std::map<char, std::string>& res, const Node* root, std::string cur)
{
    if (root->left != nullptr)
        treeParse(res, root->left, cur + "0");
    if (root->right != nullptr)
        treeParse(res, root->right, cur + "1");
    else
        res.insert(std::pair<char, std::string>(root->c, cur));
}

void Huffman::readFile(const std::string& _filename)
{
    std::ifstream in(_filename);
    if (!in.is_open())
        throw std::runtime_error("Can't find file named [" + _filename + "]");
    else
    {
        std::stringstream ss;
        while (in >> ss.rdbuf())
        {
        }
        text = ss.str();
    }
}

void Huffman::countChars()
{
    freqTable.clear();
    for (char c : text)
    {
        if (freqTable.find(c) == freqTable.end())
            freqTable[c] = 1;
        else
            freqTable[c] += 1;
    }
}

void Huffman::buildHuffmanCode()
{
    auto cmp = [](Node* l, Node* r) { return l->f > r->f; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> Q(cmp);
    for (auto el : freqTable)
        Q.emplace(new Node(el.first, el.second));
    Node* t;
    for (int i = 1; i <= freqTable.size() - 1; ++i)
    {
        Node* z = new Node('\\', 0);
        z->left = Q.top();
        Q.pop();
        z->right = Q.top();
        Q.pop();
        z->f = z->left->f + z->right->f;
        Q.push(z);
    }
    const Node* root = Q.top();
    Q.pop();
    treeParse(huffmanTable, root, "");
    treeRoot = root;
}

void Huffman::build()
{
    countChars();
    buildHuffmanCode();
}

std::vector<bool> Huffman::transform()
{
    std::vector<bool> res;
    for (char c : text)
    {
        std::string& tmp = huffmanTable[c];
        for (char c : tmp)
            res.push_back(c - '0');
    }
    return std::move(res);
}

void Huffman::transform(std::ostream& out)
{
    for (char c : text)
    {
        std::string& tmp = huffmanTable[c];
        for (char c : tmp)
            out << (c - '0');
    }
}

void Huffman::restore(std::string filename, std::ostream& out)
{
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::runtime_error("Can't find file named [" + filename + "]");

    std::stringstream ss;
    while (in >> ss.rdbuf())
        ;
    std::string txt(ss.str());
    std::string res;
    Node* cur = (Node*)treeRoot;
    for (char c : txt)
    {
        if (c == '0')
            cur = cur->left;
        else
            cur = cur->right;

        if (cur->left == nullptr)
        {
            res += cur->c;
            cur = (Node*)treeRoot;
        }
    }
    out << res;
    // return std::move(res);
}