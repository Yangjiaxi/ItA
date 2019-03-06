#include <map>

template <class T>
class Node
{
   public:
    T no;
    int w;
    Node* next;
    Node(T _no, int _w) : no(_no), w(_w), next(nullptr) {}
    Node(T _no) : no(_no), w(1), next(nullptr) {}
};

template <class T>
class Graph
{
   public:
    std::map<T, Node<T>*> adjList;
    Graph() = default;
    ~Graph() = default;

    void add(T u, T v)
    {
        Node<T>* t = new Node<T>(v);
        t->next = adjList[u];
        adjList[u] = t;
    }

    void output()
    {
        for (auto el : adjList)
        {
            std::cout << el.first << "|:";
            Node<T>* t = el.second;
            while (t != nullptr)
            {
                std::cout << "->[" << t->no << "]";
                t = t->next;
            }
            std::cout << std::endl;
        }
    }
};