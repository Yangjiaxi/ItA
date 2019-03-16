#include <fstream>
#include <iostream>
#include "Graph/graph.h"

int main()
{
    std::ifstream in("graph.txt");
    Graph<char> G;
    char u, v;
    int w;
    while (in >> u >> v >> w)
    {
        G.add(u, v, w);
        G.add(v, u, w);
    }
    in.close();

    G.output();
    std::cout << "------------------------------------" << std::endl;
    Graph<char> MST = G.MST_Kruskal();

    MST.output();

    return 0;
}
