#include <fstream>
#include <iostream>
#include "Graph/graph.h"

template <class T>
void output_scc_group(std::vector<std::vector<T>>& groups, std::ostream& os)
{
    os << "{";
    for (size_t i = 0; i < groups.size(); ++i)
    {
        os << "{";
        auto& group = groups[i];
        for (size_t j = 0; j < group.size(); ++j)
        {
            os << group[j];
            if (j < group.size() - 1)
                os << ", ";
        }
        os << "}";
        if (i < groups.size() - 1)
            os << ", ";
    }
    os << "}" << std::endl;
}

int main()
{
    std::ifstream in("graph.txt");
    Graph<char> G;

    char u, v;
    while (in >> u >> v)
        G.add(u, v);

    auto groups = G.strongly_connected_component();
    output_scc_group(groups, std::cout);
    return 0;
}
