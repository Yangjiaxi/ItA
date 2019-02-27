#include <algorithm>
#include <iostream>
#include <vector>

struct act
{
    int s;
    int f;
    act(int _s, int _f) : s(_s), f(_f) {}
};

/*
    活动分配问题：
        给出n个活动的起止时间，从中选出一个最大的兼容子集(数量最多)

    直觉：
        当活动a_k结束后，如果剩余资源可供尽可能多得活用使用，那么a_k便是一个最优解，
        于是对于一个集合S，我们应该选择最先结束的活动

    最优性证明：
        令S_k为a_k结束后的任务集合，令a_m为S_k中最早结束的任务，现证明a_m在S_k决定的
        最大兼容子集A_k中
        设a_j是A_k中最早结束的任务，则
        1. 若a_j == a_m，证毕
        2. 若a_j != a_m，由于A_k中活动按照结束时间递增排序，且f_m <= f_j，
        于是用a_m替换a_j，由于满足f_j <= s_{other}，于是自然成立f_m <= s_{other}，
        这意味着在进行此次替换后，A_k'=(A_k-{a_j})U{a_m}仍是A_k的一个最大兼容子集，证毕
        综上所述：若a_m为S_k中最早结束的任务，则a_m在S_k决定的最大兼容子集A_k中
*/

/*
    贪心：
        1. 对于所有活动按照结束时间递增排序
        2. 将第一个活动a_1纳入结果A_0(->A_1)
        3. 查找剩下的活动集合中 第一个 兼容 结果集合A_k 的活动a_m，纳入集合A_k(->A_m)
        4. 重复3直到搜索结束
*/

int main()
{
    std::vector<act> t{{1, 4},  {3, 5},  {0, 6},  {5, 7},  {3, 9},  {5, 9},
                       {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
    std::sort(t.begin(), t.end(), [](act& l, act& r) { return l.f < r.f; });

    std::vector<act> res;

    res.push_back(t[0]);
    for (int i = 1; i < t.size(); ++i)
        if (res.back().f <= t[i].s)
            res.push_back(t[i]);

    std::cout << "#Activities = " << res.size() << std::endl;
    std::for_each(res.begin(), res.end(),
                  [](act& el) { std::cout << el.s << " -> " << el.f << std::endl; });
    return 0;
}
