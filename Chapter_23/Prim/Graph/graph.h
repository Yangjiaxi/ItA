#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include "DisjointSet.h"

#define INF 0x3f3f3f3f

// 边
template <class T>
class Edge
{
   public:
    T no;
    int w;
    Edge* next;
    Edge(T _no, int _w) : no(_no), w(_w), next(nullptr) {}
    Edge(T _no) : no(_no), w(1), next(nullptr) {}
    friend std::ostream& operator<<(std::ostream& os, const Edge& eg)
    {
        os << "Edge_" << eg.no << " w: " << eg.w;
        return os;
    }
};

// 节点
template <class T>
class Node
{
   public:
    T no;
    Node<T>* pre;
    int d;  // discover time
    int f;  // finish   time
    bool vis;
    Node(T _no) : d(0), f(0), vis(false), no(_no) {}
    Node() : d(0), f(0), vis(false) {}
    // for Prim use, d for key
    Node(bool _, T _no) : d(INF), vis(false), pre(nullptr), no(_no) {}

    friend std::ostream& operator<<(std::ostream& os, const Node& nd)
    {
        os << "[" << std::setw(5) << nd.no << "]{" << std::setw(3) << nd.d << " -" << std::setw(3)
           << nd.f << " vis: " << nd.vis << "}";
        return os;
    }
};

template <class T>
class Graph
{
   public:
    std::map<T, Edge<T>*> edges;
    std::map<T, Node<T>> nodes;
    Graph() = default;
    ~Graph() = default;

    bool is_DFS = false;  // 防止多次执行DFS

    // 加边，同时初始化节点
    void add(T u, T v);
    // 加赋权边
    void add(T u, T v, int w);
    // 输出
    void output();
    // 计算总权重, bidirectional=True->无向图(/=2) | False->有向图
    int total_weight(bool bidirectional);
    // 从s开始执行BFS
    void BFS(T s);
    // 执行BFS后打印s到v的路径
    void print_path_after_BFS(T s, T v);
    // 执行DFS
    void DFS();
    // 执行拓扑排序
    std::vector<T> topo_sort();
    // 得到转置图G->G^T
    Graph<T> transpose();
    // 给出所有强连通分量
    std::vector<std::vector<T>> strongly_connected_component();
    // 获得最小生成树-Kruskal
    Graph<T> MST_Kruskal();
    // 获得最小生成树-Prim
    Graph<T> MST_Prim();

   private:
    // 全局时间戳
    unsigned long g_time;
    // DFS辅助
    void DFS_visit(T u);
    void SCC_DFS_visit(T u, std::vector<T>& group);
};

template <class T>
void Graph<T>::add(T u, T v)
{
    Edge<T>* t = new Edge<T>(v);
    t->next = edges[u];
    edges[u] = t;

    if (nodes.find(u) == nodes.end())
        nodes[u] = Node<T>(u);
    if (nodes.find(v) == nodes.end())
        nodes[v] = Node<T>(v);
}

template <class T>
void Graph<T>::add(T u, T v, int w)
{
    Edge<T>* t = new Edge<T>(v, w);
    t->next = edges[u];
    edges[u] = t;

    if (nodes.find(u) == nodes.end())
        nodes[u] = Node<T>(u);
    if (nodes.find(v) == nodes.end())
        nodes[v] = Node<T>(v);
}

template <class T>
void Graph<T>::output()
{
    for (auto node_p : nodes)
    {
        Node<T>& node = node_p.second;
        std::cout << node << "|:";
        Edge<T>* t = edges[node.no];
        while (t != nullptr)
        {
            std::cout << "->[" << t->no << " " << std::setw(2) << t->w << "]";
            t = t->next;
        }
        std::cout << std::endl;
    }
}

template <class T>
int Graph<T>::total_weight(bool bidirectional)
{
    int cost = 0;
    for (auto node_p : nodes)
    {
        for (Edge<T>* v = edges[node_p.first]; v != nullptr; v = v->next)
        {
            cost += v->w;
        }
    }
    return bidirectional ? (cost / 2) : cost;
}

template <class T>
void Graph<T>::BFS(T s)
{
    std::cout << "BFS from " << s << std::endl;
    nodes[s].d = 0;
    nodes[s].vis = true;
    nodes[s].pre = 0;
    std::queue<T> Q;
    Q.push(s);
    T u;
    Edge<T>* v;

    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();
        v = edges[u];
        while (v != nullptr)
        {
            if (!nodes[v->no].vis)
            {
                nodes[v->no].vis = true;
                nodes[v->no].d = nodes[u].d + 1;
                nodes[v->no].pre = &nodes[u];
                std::cout << "Vis : " << v->no << " dis : " << nodes[v->no].d << " pre : " << u
                          << std::endl;
                Q.push(v->no);
            }
            v = v->next;
        }
    }
}

template <class T>
void Graph<T>::print_path_after_BFS(T s, T v)
{
    if (v == s)
        std::cout << s;
    else if (nodes[v].pre == nullptr)
        std::cout << "No such path from " << s << " to " << v << std::endl;
    else
    {
        print_path_after_BFS(s, nodes[v].pre->no);
        std::cout << "->" << v;
    }
}

template <class T>
void Graph<T>::DFS()
{
    if (is_DFS)
    {
        std::cout << "Already performd DFS on this Graph!" << std::endl;
        return;
    }
    g_time = 0;
    for (std::pair<T, Node<T>> node_p : nodes)
    {
        if (!node_p.second.vis)
            DFS_visit(node_p.first);
    }
    is_DFS = true;
}

template <class T>
void Graph<T>::DFS_visit(T u)
{
    ++g_time;
    nodes[u].d = g_time;
    nodes[u].vis = true;

    for (Edge<T>* v = edges[u]; v != nullptr; v = v->next)
    {
        if (!nodes[v->no].vis)
        {
            nodes[v->no].pre = &nodes[u];
            DFS_visit(v->no);
        }
    }
    ++g_time;
    nodes[u].f = g_time;
}

template <class T>
std::vector<T> Graph<T>::topo_sort()
{
    DFS();
    using pT = std::pair<T, unsigned long>;
    std::vector<pT> tmp;
    for (auto node : nodes)
        tmp.push_back(std::make_pair(node.first, node.second.f));
    std::sort(tmp.begin(), tmp.end(), [](const pT l, const pT r) { return l.second > r.second; });
    std::vector<T> res;

    for (auto tt : tmp)
        res.push_back(tt.first);

    return std::move(res);
}

template <class T>
Graph<T> Graph<T>::transpose()
{
    Graph<T> G_T;
    for (std::pair<T, Edge<T>*> ep : edges)
    {
        T u = ep.first;
        Edge<T>* v = edges[u];
        while (v != nullptr)
        {
            G_T.add(v->no, u);
            v = v->next;
        }
    }
    // G_T.output();
    return std::move(G_T);
}
template <class T>
void Graph<T>::SCC_DFS_visit(T u, std::vector<T>& group)
{
    nodes[u].vis = true;
    group.push_back(u);
    for (Edge<T>* v = edges[u]; v != nullptr; v = v->next)
    {
        if (!nodes[v->no].vis)
        {
            nodes[v->no].pre = &nodes[u];
            SCC_DFS_visit(v->no, group);
        }
    }
}

template <class T>
std::vector<std::vector<T>> Graph<T>::strongly_connected_component()
{
    Graph G_T = transpose();
    std::vector<T> topo = topo_sort();
    std::vector<std::vector<T>> groups;
    for (T tp : topo)
    {
        if (!G_T.nodes[tp].vis)
        {
            std::vector<T> group;
            G_T.SCC_DFS_visit(tp, group);
            groups.push_back(group);
        }
    }
    return std::move(groups);
}

template <class T>
Graph<T> Graph<T>::MST_Kruskal()
{
    DisjointSet<T> edges_set;
    for (std::pair<T, Node<T>> node_p : nodes)
        edges_set.make_set(node_p.first);

    using ppTTi = std::pair<std::pair<T, T>, int>;
    std::vector<ppTTi> edges_vec;

    for (std::pair<T, Edge<T>*> ep : edges)
    {
        T u = ep.first;
        for (Edge<T>* v = edges[u]; v != nullptr; v = v->next)
            edges_vec.push_back({{u, v->no}, v->w});
    }

    std::sort(edges_vec.begin(), edges_vec.end(),
              [](ppTTi l, ppTTi r) { return l.second <= r.second; });

    Graph<T> MST;
    for (ppTTi edge : edges_vec)
    {
        T u = edge.first.first;
        T v = edge.first.second;
        int w = edge.second;
        if (edges_set.find_set(u) != edges_set.find_set(v))
        {
            MST.add(u, v, w);
            MST.add(v, u, w);
            edges_set.set_union(u, v);
        }
    }
    return std::move(MST);
}

template <class T>
Graph<T> Graph<T>::MST_Prim()
{
    using pTi = std::pair<T, int>;
    auto cmp = [](pTi& l, pTi& r) { return l.second > r.second; };
    std::priority_queue<pTi, std::vector<pTi>, decltype(cmp)> Q(cmp);

    for (auto& node_p : nodes)
    {
        node_p.second.vis = false;  // 不在MST中
        node_p.second.d = INF;      // 相当于key
    }

    T s = nodes.begin()->first;
    Q.push(std::make_pair(s, 0));
    nodes[s].d = 0;

    while (!Q.empty())
    {
        T u = Q.top().first;
        Q.pop();
        nodes[u].vis = true;  // 在MST中

        for (Edge<T>* vp = edges[u]; vp != nullptr; vp = vp->next)
        {
            T v = vp->no;
            int w = vp->w;
            if (!nodes[v].vis && nodes[v].d > w)  // 如果v不在MST中且权重小
            {
                nodes[v].d = w;
                nodes[v].pre = &nodes[u];
                Q.push(std::make_pair(v, w));
            }
        }
    }

    Graph<T> MST;
    for (auto& node_p : nodes)
    {
        Node<T>& node = node_p.second;
        if (node_p.first != s)
        {
            MST.add(node.no, node.pre->no, node.d);
            MST.add(node.pre->no, node.no, node.d);
        }
    }
    return std::move(MST);
}