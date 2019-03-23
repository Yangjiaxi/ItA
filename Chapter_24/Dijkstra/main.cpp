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
    }
    in.close();
    char start = 's';
    std::vector<char> query_list{'s', 't', 'x', 'y', 'z'};

    G.output();
    std::cout << "------------------------------------" << std::endl;

    std::cout << "Dijkstra : " << std::endl;
    G.dijkstra(start);
    for (char v : query_list)
    {
        std::cout << "From [" << start << "] to [" << v << "]" << std::endl;
        std::cout << "\tdis: " << G.nodes[v].d << std::endl;
        std::cout << "\tpath: ";
        auto path = G.single_source_path(v);
        for (int i = 0; i < path.size() - 1; ++i)
            std::cout << path[i] << " -> ";
        std::cout << path[path.size() - 1] << std::endl;
    }

    return 0;
}
