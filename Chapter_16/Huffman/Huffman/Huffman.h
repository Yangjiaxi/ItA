#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>

/*
    哈夫曼编码：
        -> 输入一串文本
        -> 统计字频
        -> 生成哈夫曼树
        -> 生成哈弗曼编码映射
        -> 变换原文本

*/

typedef struct _Node
{
    char c;  // key
    int f;   // freq
    struct _Node* left;
    struct _Node* right;
    _Node(char _c, int _f) : c(_c), f(_f), left(nullptr), right(nullptr) {}
} Node;

class Huffman
{
    bool comp = [](std::pair<char, int> a, std::pair<char, int> b) { return a.second > b.second; };

   private:
    std::string text;
    std::unordered_map<char, int> freqTable;
    std::map<char, std::string> huffmanTable;
    const Node* treeRoot;

    void countChars();
    void buildHuffmanCode();
    void treeParse(std::map<char, std::string>& res, const Node* root, std::string cur);

   public:
    Huffman() {}
    ~Huffman() = default;
    Huffman(std::string&& _text) : text(_text) {}
    Huffman(std::string& _text) : text(_text) {}

    void readFile(std::string&& _filename) { readFile(_filename); }
    void readFile(const std::string& _filename);
    void setText(std::string&& _text) { setText(_text); }
    void setText(std::string& _text) { text = _text; }
    std::string getText() { return std::string(text); }

    std::unordered_map<char, int> getFreqTable() { return freqTable; }
    std::map<char, std::string> getHuffmanTable() { return huffmanTable; }

    void build();
    std::vector<bool> transform();
    void transform(std::ostream& out);
    void transform(std::ostream&& out) { transform(out); }
    void restore(std::string filename, std::ostream& out);
    void restore(std::string filename, std::ostream&& out) { return restore(filename, out); }
};
