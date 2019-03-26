#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

template <class T>
class SetNode
{
   public:
    T data;
    int rank;
    SetNode<T>* p;
    SetNode() : p(this), rank(0) {}
    ~SetNode() = default;
    SetNode(T _data) : p(this), data(_data), rank(0) {}
};

template <class T>
class DisjointSet
{
   public:
    std::map<T, SetNode<T>*> set_data;
    DisjointSet() = default;
    ~DisjointSet() = default;

    // COMMON:
    // 向集合加入元素T x
    void make_set(const T& x) { set_data.insert(std::make_pair(x, new SetNode<T>(x))); }
    void make_set(const T&& x) { return make_set(x); }
    // 合并拥有元素x与y的两个集合
    void set_union(T& x, T& y) { link(find_set(set_data[x]), find_set(set_data[y])); }
    void set_union(T&& x, T&& y) { set_union(x, y); }
    // 连接两个树
    void link(SetNode<T>* x, SetNode<T>* y)
    {
        if (x->rank > y->rank)
            y->p = x;
        else
        {
            x->p = y;
            if (x->rank == y->rank)
                y->rank += 1;
        }
    }
    // 找到拥有元素x的树，返回代表节点(根节点)的指针
    SetNode<T>* find_set(SetNode<T>* x)
    {
        if (x != x->p)
            x->p = find_set(x->p);
        return x->p;
    }
    SetNode<T>* find_set(T& x) { return find_set(set_data[x]); }
    SetNode<T>* find_set(T&& x) { return find_set(set_data[x]); }

    // 使用vector<T>初始化
    void init_set(std::vector<T>& vl)
    {
        std::for_each(vl.begin(), vl.end(), [&](T& el) { make_set(el); });
    }
};