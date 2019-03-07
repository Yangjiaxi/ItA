#include <map>
#include <queue>

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
};

// 节点
template <class T>
class Node
{
   public:
    T no;
    Node<T>* pre;
    int d;
    bool vis;
    Node(T _no) : d(0x3f3f3f3f), vis(false), no(_no) {}
    Node() : d(0x3f3f3f3f), vis(false) {}
};

template <class T>
class Graph
{
   public:
    std::map<T, Edge<T>*> edges;
    std::map<T, Node<T>> nodes;
    Graph() = default;
    ~Graph() = default;

    // 加边，同时初始化节点
    void add(T u, T v);
    // 输出
    void output();
    // 从s开始执行BFS
    void BFS(T s);
    // 执行BFS后打印s到v的路径
    void print_path_after_BFS(T s, T v);
};

template <class T>
void Graph<T>::add(T u, T v)
{
    Edge<T>* t = new Edge<T>(v);
    t->next = edges[u];
    edges[u] = t;

    if (nodes.find(u) == nodes.end()) nodes[u] = Node<T>(u);
    if (nodes.find(v) == nodes.end()) nodes[v] = Node<T>(v);
}

template <class T>
void Graph<T>::output()
{
    for (std::pair<T, Node<T>> node : nodes)
    {
        std::cout << "[" << node.first << "]{d:" << node.second.d << " vis:" << node.second.vis
                  << "}|:";
        Edge<T>* t = edges[node.first];
        while (t != nullptr)
        {
            std::cout << "->[" << t->no << "]";
            t = t->next;
        }
        std::cout << std::endl;
    }
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