#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Huffman/Huffman.h"

using std::cout;
using std::endl;

int main()
{
    Huffman huffman;
    const std::string infile = "read.in";
    const std::string outfile = "tran.dat";
    const std::string restore = "restore.txt";
    // read and build huffman code system
    huffman.readFile(infile);
    huffman.build();

    // show data
    auto hcTable = huffman.getHuffmanTable();
    auto _fqTable = huffman.getFreqTable();

    using pType = std::pair<char, int>;
    std::vector<pType> fqTable(_fqTable.begin(), _fqTable.end());
    std::sort(fqTable.begin(), fqTable.end(), [](pType a, pType b) { return a.second > b.second; });

    cout << "---------------------- Huffman Code Table ----------------------" << endl;
    cout << "char" << std::setw(20) << "frequency" << std::setw(20) << "Huffman code" << endl;
    for (auto el : fqTable)
    {
        cout << el.first;
        cout << std::setw(20) << el.second;
        cout << std::setw(20) << hcTable[el.first];
        cout << endl;
    }

    //
    cout << "------------------------ After Tranafer -----------------------" << endl;
    auto res = huffman.transform();
    cout << "size : " << res.size() << endl;
    std::for_each(res.begin(), res.end(), [](const bool c) { cout << c; });

    cout << endl << "----------------------- And Restore Data ----------------------" << endl;
    huffman.transform(std::ofstream(outfile));
    huffman.restore(outfile, std::ofstream(restore));
    return 0;
}
