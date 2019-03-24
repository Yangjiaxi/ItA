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

    auto res_p = G.all_pairs_matrix();
    auto dis = std::move(res_p.first);
    auto pre = std::move(res_p.second);

    for (auto& up : G.nodes)
    {
        T u = up.first;
        for (auto& vp : G.nodes)
        {
            T v = vp.first;
            std::cout << std::setw(5) << ((pre[u][v] != nullptr) ? pre[u][v]->no : 'N');
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
                std::for_each(path.begin(), path.end(), [](char el) { std::cout << " ->" << el; });
            }
            std::cout << std::endl;
        }
    }
    return 0;
}

// ------------------------------------
//     N    1    1    2    1
//     4    N    4    2    2
//     4    3    N    2    1
//     4    3    4    N    1
//     4    3    4    5    N
// From [1]:
//         To [1]: dis :     0
//         To [2]: dis :     1     Path :  ->1 ->2
//         To [3]: dis :    -3     Path :  ->1 ->3
//         To [4]: dis :     2     Path :  ->1 ->2 ->4
//         To [5]: dis :    -4     Path :  ->1 ->5
// From [2]:
//         To [1]: dis :     3     Path :  ->2 ->4 ->1
//         To [2]: dis :     0
//         To [3]: dis :    -4     Path :  ->2 ->4 ->3
//         To [4]: dis :     1     Path :  ->2 ->4
//         To [5]: dis :    -1     Path :  ->2 ->5
// From [3]:
//         To [1]: dis :     7     Path :  ->3 ->2 ->4 ->1
//         To [2]: dis :     4     Path :  ->3 ->2
//         To [3]: dis :     0
//         To [4]: dis :     5     Path :  ->3 ->2 ->4
//         To [5]: dis :     3     Path :  ->3 ->2 ->4 ->1 ->5
// From [4]:
//         To [1]: dis :     2     Path :  ->4 ->1
//         To [2]: dis :    -1     Path :  ->4 ->3 ->2
//         To [3]: dis :    -5     Path :  ->4 ->3
//         To [4]: dis :     0
//         To [5]: dis :    -2     Path :  ->4 ->1 ->5
// From [5]:
//         To [1]: dis :     8     Path :  ->5 ->4 ->1
//         To [2]: dis :     5     Path :  ->5 ->4 ->3 ->2
//         To [3]: dis :     1     Path :  ->5 ->4 ->3
//         To [4]: dis :     6     Path :  ->5 ->4
//         To [5]: dis :     0