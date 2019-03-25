#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include "DisjointSet.h"

using std::cout;
using std::endl;
using std::make_pair;
using std::map;
using std::move;
using std::pair;
using std::setw;
using std::vector;

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

    friend std::ostream& operator<<(std::ostream& os, const Node& nd)
    {
        os << "[" << setw(5) << nd.no << "]{" << setw(3) << nd.d << " -" << setw(3) << nd.f
           << " vis: " << nd.vis << "}";
        return os;
    }
};

template <class T>
class Graph
{
   public:
    map<T, Edge<T>*> edges;
    map<T, Node<T>> nodes;
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
    vector<T> topo_sort();
    // 得到转置图G->G^T
    Graph<T> transpose();
    // 给出所有强连通分量
    vector<vector<T>> strongly_connected_component();
    // 获得最小生成树-Kruskal
    Graph<T> MST_Kruskal();
    // 获得最小生成树-Prim
    Graph<T> MST_Prim();
    // 单源最短路算法Bellman-Ford
    // return   true  : 正确执行，数据合法
    //          false : 存在从源点可达的权值为负的环路
    bool bellman_ford(T s);
    // 单源最短路算法Dijkstra
    void dijkstra(T s);
    // 单源最短路路径(正序s->v)
    vector<T> single_source_path(T v);
    // 全节点对最短路，使用矩阵乘法重复平方技术
    pair<map<T, map<T, int>>, map<T, map<T, Node<T>*>>> all_pairs_matrix();
    // 根据Pre矩阵获得u->v的路径
    vector<T> all_pairs_path(T u, T v, map<T, map<T, Node<T>*>>& P);
    // 全节点对最短路，Floya-Warshall算法
    pair<map<T, map<T, int>>, map<T, map<T, Node<T>*>>> floyd();

   private:
    // 获得u->v的权重，没有这样的路则返回INF
    int w(T u, T v);
    // 全局时间戳
    unsigned long g_time;
    // DFS辅助
    void DFS_visit(T u);
    // 强连通分量DFS辅助
    void SCC_DFS_visit(T u, vector<T>& group);
    // 单源最短路初始化
    void initialize_single_source(T s);
    // 松弛操作 u, v, w=w(u->v)
    bool relax(T u, T v, int w);
    // 扩展路，用于基于矩阵乘法的全节点最短路算法
    map<T, map<T, int>> extend_all_pairs(map<T, map<T, int>>& L, map<T, map<T, int>>& W);
};

template <class T>
int Graph<T>::w(T u, T v)
{
    if (u == v)
        return 0;

    for (Edge<T>* vp = edges[u]; vp != nullptr; vp = vp->next)
        if (vp->no == v)
            return vp->w;

    return INF;
}

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
    for (auto& node_p : nodes)
    {
        Node<T>& node = node_p.second;
        cout << node << "|:";
        Edge<T>* t = edges[node.no];
        while (t != nullptr)
        {
            cout << "->[" << t->no << " " << setw(2) << t->w << "]";
            t = t->next;
        }
        cout << endl;
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
    cout << "BFS from " << s << endl;
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
                cout << "Vis : " << v->no << " dis : " << nodes[v->no].d << " pre : " << u << endl;
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
        cout << s;
    else if (nodes[v].pre == nullptr)
        cout << "No such path from " << s << " to " << v << endl;
    else
    {
        print_path_after_BFS(s, nodes[v].pre->no);
        cout << "->" << v;
    }
}

template <class T>
void Graph<T>::DFS()
{
    if (is_DFS)
    {
        cout << "Already performd DFS on this Graph!" << endl;
        return;
    }
    g_time = 0;
    for (auto& node_p : nodes)
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
vector<T> Graph<T>::topo_sort()
{
    DFS();
    using pT = pair<T, unsigned long>;
    vector<pT> tmp;
    for (auto& node : nodes)
        tmp.push_back(make_pair(node.first, node.second.f));
    std::sort(tmp.begin(), tmp.end(), [](const pT l, const pT r) { return l.second > r.second; });
    vector<T> res;

    for (auto tt : tmp)
        res.push_back(tt.first);

    return move(res);
}

template <class T>
Graph<T> Graph<T>::transpose()
{
    Graph<T> G_T;
    for (pair<T, Edge<T>*> ep : edges)
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
    return move(G_T);
}
template <class T>
void Graph<T>::SCC_DFS_visit(T u, vector<T>& group)
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
vector<vector<T>> Graph<T>::strongly_connected_component()
{
    Graph G_T = transpose();
    vector<T> topo = topo_sort();
    vector<vector<T>> groups;
    for (T tp : topo)
    {
        if (!G_T.nodes[tp].vis)
        {
            vector<T> group;
            G_T.SCC_DFS_visit(tp, group);
            groups.push_back(group);
        }
    }
    return move(groups);
}

template <class T>
Graph<T> Graph<T>::MST_Kruskal()
{
    DisjointSet<T> edges_set;
    for (auto& node_p : nodes)
        edges_set.make_set(node_p.first);

    using ppTTi = pair<pair<T, T>, int>;
    vector<ppTTi> edges_vec;

    for (pair<T, Edge<T>*> ep : edges)
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
    return move(MST);
}

template <class T>
Graph<T> Graph<T>::MST_Prim()
{
    using pTi = pair<T, int>;
    auto cmp = [](pTi& l, pTi& r) { return l.second > r.second; };
    std::priority_queue<pTi, vector<pTi>, decltype(cmp)> Q(cmp);

    for (auto& node_p : nodes)
    {
        node_p.second.vis = false;  // 不在MST中
        node_p.second.d = INF;      // 相当于key
    }

    T s = nodes.begin()->first;
    Q.push(make_pair(s, 0));
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
                Q.push(make_pair(v, w));
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
    return move(MST);
}

template <class T>
void Graph<T>::initialize_single_source(T s)
{
    for (auto& node_p : nodes)
    {
        node_p.second.d = INF;
        node_p.second.pre = nullptr;
    }
    nodes[s].d = 0;
}

template <class T>
bool Graph<T>::relax(T u, T v, int w)
{
    if (nodes[v].d > nodes[u].d + w)
    {
        nodes[v].d = nodes[u].d + w;
        nodes[v].pre = &nodes[u];
        return true;
    }
    return false;
}

template <class T>
bool Graph<T>::bellman_ford(T s)
{
    initialize_single_source(s);
    for (int i = 1; i <= nodes.size() - 1; ++i)
    {
        for (auto& node_p : nodes)
        {
            T u = node_p.first;
            for (Edge<T>* v = edges[u]; v != nullptr; v = v->next)
                relax(u, v->no, v->w);
        }
    }
    for (auto& node_p : nodes)
    {
        T u = node_p.first;
        for (Edge<T>* v = edges[u]; v != nullptr; v = v->next)
            if (nodes[v->no].d > node_p.second.d + v->w)
            {
                return false;
            }
    }
    return true;
}

template <class T>
vector<T> Graph<T>::single_source_path(T v)
{
    vector<T> res;
    Node<T>* cur = &nodes[v];
    while (cur != nullptr)
    {
        res.push_back(cur->no);
        cur = cur->pre;
    }
    std::reverse(res.begin(), res.end());
    return move(res);
}

template <class T>
void Graph<T>::dijkstra(T s)
{
    initialize_single_source(s);

    using pTi = pair<T, int>;
    auto cmp = [](pTi& l, pTi& r) { return l.second > r.second; };
    std::priority_queue<pTi, vector<pTi>, decltype(cmp)> Q(cmp);

    Q.push(make_pair(s, 0));
    nodes[s].d = 0;

    while (!Q.empty())
    {
        T u = Q.top().first;
        Q.pop();

        for (Edge<T>* vp = edges[u]; vp != nullptr; vp = vp->next)
        {
            T v = vp->no;
            int w = vp->w;
            if (relax(u, v, w))
                Q.push(make_pair(v, nodes[v].d));
        }
    }
}

template <class T>
map<T, map<T, int>> Graph<T>::extend_all_pairs(map<T, map<T, int>>& L, map<T, map<T, int>>& W)
{
    map<T, map<T, int>> L_p;
    for (auto& np : nodes)
    {
        L_p[np.first] = move(map<T, int>());
    }

    for (auto& ip : nodes)
    {
        T i = ip.first;
        for (auto& jp : nodes)
        {
            T j = jp.first;
            L_p[i][j] = INF;
            for (auto& kp : nodes)
            {
                T k = kp.first;
                L_p[i][j] = std::min(L_p[i][j], L[i][k] + W[k][j]);
            }
        }
    }

    return move(move(L_p));
}

template <class T>
pair<map<T, map<T, int>>, map<T, map<T, Node<T>*>>> Graph<T>::all_pairs_matrix()
{
    map<T, map<T, int>> res;
    int m = 1;
    int n = nodes.size();

    map<T, map<T, Node<T>*>> P;

    for (auto& up : nodes)
    {
        T u = up.first;
        res[u] = move(map<T, int>());
        for (auto& vp : nodes)
        {
            T v = vp.first;
            res[u][v] = w(u, v);
            if (res[u][v] != INF && u != v)
                P[u][v] = &nodes[u];
            else
                P[u][v] = nullptr;
        }
    }

    while (m < n - 1)
    {
        res = extend_all_pairs(res, res);
        m *= 2;
    }

    for (auto& ip : nodes)
    {
        T i = ip.first;
        for (auto& jp : nodes)
        {
            T j = jp.first;
            for (auto& kp : nodes)
            {
                T k = kp.first;
                if (j != k && res[i][k] + w(k, j) == res[i][j])
                    P[i][j] = &nodes[k];
            }
        }
    }

    return move(make_pair(res, P));
}

template <class T>
void __inner_all_pairs_path(T i, T j, map<T, map<T, Node<T>*>>& P, vector<T>& res)
{
    if (i == j)
        res.push_back(i);
    else if (P[i][j] == nullptr)
        std::cerr << "No such path from " << i << " to " << j << endl;
    else
    {
        __inner_all_pairs_path(i, P[i][j]->no, P, res);
        res.push_back(j);
    }
}

template <class T>
vector<T> Graph<T>::all_pairs_path(T u, T v, map<T, map<T, Node<T>*>>& P)
{
    vector<T> res;
    __inner_all_pairs_path(u, v, P, res);
    return move(res);
}

template <class T>
pair<map<T, map<T, int>>, map<T, map<T, Node<T>*>>> Graph<T>::floyd()
{
    map<T, map<T, int>> res;
    map<T, map<T, Node<T>*>> P;

    for (auto& up : nodes)
    {
        T u = up.first;
        res[u] = move(map<T, int>());
        for (auto& vp : nodes)
        {
            T v = vp.first;
            res[u][v] = w(u, v);
            if (res[u][v] != INF && u != v)
                P[u][v] = &nodes[u];
            else
                P[u][v] = nullptr;
        }
    }

    for (auto& kp : nodes)
    {
        T k = kp.first;
        for (auto& ip : nodes)
        {
            T i = ip.first;
            for (auto& jp : nodes)
            {
                T j = jp.first;
                if (res[i][k] + res[k][j] < res[i][j])
                {
                    res[i][j] = res[i][k] + res[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }

    return move(make_pair(res, P));
}