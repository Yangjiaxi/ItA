#include <fstream>
#include <iostream>
#include "Graph/graph.h"

int main()
{
    using T = char;

    std::ifstream in("graph.txt");
    Graph<T> G;
    T u, v;
    int w;
    while (in >> u >> v >> w)
    {
        G.add(u, v, w);
    }
    in.close();

    G.output();
    std::cout << "------------------------------------" << std::endl;

    auto res_p = G.floyd();
    auto dis = std::move(res_p.first);
    auto pre = std::move(res_p.second);

    for (auto& up : G.nodes)
    {
        T u = up.first;
        for (auto& vp : G.nodes)
        {
            T v = vp.first;
            std::cout << std::setw(5)
                      << ((pre[u][v] != nullptr) ? pre[u][v]->no : 'N');
        }
        std::cout << std::endl;
    }

    for (auto& up : G.nodes)
    {
        T u = up.first;
        std::cout << "From [" << u << "]:" << std::endl;
        for (auto& vp : G.nodes)
        {
            T v = vp.first;
            std::cout << "\tTo [" << v << "]: ";
            std::cout << "dis : " << std::setw(5) << dis[u][v];
            if (u != v)
            {
                std::cout << "\tPath : ";
                auto path = G.all_pairs_path(u, v, pre);
                std::for_each(path.begin(), path.end(),
                              [](char el) { std::cout << " ->" << el; });
            }
            std::cout << std::endl;
        }
    }
    return 0;
}