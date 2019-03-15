#include <fstream>
#include <iostream>
#include <string>
#include "DisjointSet/DisjointSet.h"

/*
 *  求无向图的连通分量，使用并查集实现，使用启发式按秩合并与路径压缩
 */

int main()
{
    std::ifstream in("graph.txt");
    DisjointSet<char> ds;
    int n;
    in >> n;
    char t;
    for (int i = 1; i <= n; ++i)
    {
        in >> t;
        ds.make_set(t);
    }

    char u, v;
    while (in >> u >> v)
        ds.set_union(u, v);

    for (auto p : ds.set_data)
    {
        std::cout << p.first << " in : " << ds.find_set((char)p.first)->data << std::endl;
    }
    return 0;
}
