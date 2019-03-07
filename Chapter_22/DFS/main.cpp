#include <fstream>
#include <iostream>
#include "Graph/graph.h"

int main()
{
    std::ifstream in("graph.txt");
    Graph<char> g;

    char u, v;
    while (in >> u >> v)
    {
        g.add(u, v);
    }
    g.output();
    g.DFS();
    std::cout << "After DFS : " << std::endl;
    g.output();
    std::cout << std::endl;

    return 0;
}
