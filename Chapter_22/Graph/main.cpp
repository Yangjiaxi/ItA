#include <fstream>
#include <iostream>
#include "graph.h"

int main()
{
    std::ifstream in("graph.txt");
    Graph<char> g;

    char u, v;
    while (in >> u >> v)
    {
        g.add(u, v);
        g.add(v, u);
    }
    g.output();

    return 0;
}
