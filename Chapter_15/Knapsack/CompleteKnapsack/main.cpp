#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::vector;

/*
    n=4, m=10

    w = {2, 3, 4, 7}
    v = {1, 3, 5, 9}

    output : 12
*/
int main(int, char**)
{
    int n = 2;   // 物品数量
    int m = 10;  // 背包空间
    vector<int> w = {-1, 1, 2};
    vector<int> v = {-1, 1, 3};

    // 1. 直接枚举可能个数，作为第三个状态
    vector<vector<int>> f1(n + 1);
    for (int i = 0; i <= n; ++i)
        f1[i].resize(m + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (int k = 0; k <= j / w[i]; ++k)
            {
                if (j - k * w[i] >= 0)
                {
                    f1[i][j] = max(f1[i][j], f1[i - 1][j - k * w[i]] + k * v[i]);
                }
            }
        }
    }
    cout << "完全背包 : " << f1[n][m] << endl << endl;

    // 2. 一维正序
    /*
        首先考虑01背包的一维情况，那里的内部循环是For(j=m->0)，目的就是为了满足转移方程
        f[j] = f[j-w[i]]+v[i]，为了使f[j]的依赖项f[j-w[i]]不在f[j]之前被求，
        也就是说，每次决策的物品i在当前状态(容量j)下一定没有被选择过
        -----------------------------------------------
        如果从正向处理内层循环，对于阶段i容量为j的子问题由同阶段i的子问题k们(k<j)转移而来，而对于子问题k们已经考察过的
        物品w[i]，子问题j仍会去考虑。也就是说，子问题j依赖于同阶段下的小容量问题，而由动态规划的最优子结构性质可得，
        f[j]为子问题j的最优解
        -----------------------------------------------
        换个角度考虑两种背包问题的代码差异：
        对于01背包要求每个物品只能选一次，也就是不同阶段对于物品的选择有抢占制，一个资源在一时刻只能被持有一次，这也便是子问题的无关性；
        而完全背包则不存在资源冲突问题，每一个资源是可以被多次共享的

        子问题的无关性 详细讨论见 算法导论CLRS(中文第三版)P218.
    */
    // 2.1 01背包(用于对比)
    vector<int> f2(m + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = m; j >= w[i]; --j)
        {
            f2[j] = max(f2[j], f2[j - w[i]] + v[i]);
        }
    }
    std::for_each(f2.cbegin(), f2.cend(), [](const int ele) { cout << ele << "\t"; });
    cout << endl << "01背包 : " << f2[m] << endl << endl;

    // 2.2 完全背包，注意内部循环
    f2.clear();
    f2.resize(m + 1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = w[i]; j <= m; ++j)  // For(j=0->m)
        {
            f2[j] = max(f2[j], f2[j - w[i]] + v[i]);
        }
    }

    std::for_each(f2.cbegin(), f2.cend(), [](const int ele) { cout << ele << "\t"; });
    cout << endl << "完全背包 : " << f2[m] << endl << endl;

    // 3. 抽象
    vector<int> f3(m + 1);
    auto CompletePack = [&f3, m](int weight, int value) {
        for (int j = weight; j <= m; ++j)
            f3[j] = max(f3[j], f3[j - weight] + value);
    };
    for (int i = 1; i <= n; ++i)
        CompletePack(w[i], v[i]);
    std::for_each(f3.cbegin(), f3.cend(), [](const int ele) { cout << ele << "\t"; });
    cout << endl << "完全背包 : " << f3[m] << endl << endl;
    return 0;
}
