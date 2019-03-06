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
        g.add(v, u);
    }
    g.output();
    g.BFS('s');
    g.output();
    g.print_path_after_BFS('s', 'y');
    std::cout << std::endl;

    return 0;
}
