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

    // G.output();
    std::cout << "------------------------------------" << std::endl;
    Graph<char> MST_Prim = G.MST_Prim();
    Graph<char> MST_Kruskal = G.MST_Kruskal();

    MST_Prim.output();
    std::cout << "Total weight of MST-Prim : " << MST_Prim.total_weight(true) << std::endl;

    std::cout << "------------------------------------" << std::endl;

    MST_Kruskal.output();
    std::cout << "Total weight of MST-Kruskal : " << MST_Kruskal.total_weight(true) << std::endl;

    return 0;
}
