#include <fstream>
#include <iostream>
#include "Graph/graph.h"

int main()
{
    std::ifstream in("graph.txt");
    Graph<std::string> g;

    std::string u, v;
    while (in >> u >> v)
        g.add(u, v);

    g.DFS();

    auto topo_res = g.topo_sort();

    std::cout << " DO : ";
    std::for_each(topo_res.cbegin(), topo_res.cend(),
                  [](const std::string s) { std::cout << "->" << s; });
    std::cout << std::endl;

    return 0;
}
