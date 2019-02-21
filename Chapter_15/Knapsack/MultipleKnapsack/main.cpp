#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::for_each;
using std::max;
using std::vector;
/*
    多重背包问题：
        n种物品，背包容量m，
        第i种物品有c[i]件，每件占用空间w[i]，价值v[i]
*/

int main()
{
    int n = 5;
    int m = 5;
    vector<int> c = {-1, 2, 1, 3, 4, 2};
    vector<int> w = {-1, 1, 3, 2, 4, 5};
    vector<int> v = {-1, 200, 100, 300, 150, 350};

    // int n = 2;
    // int m = 8;
    // vector<int> c = {-1, 4, 2};
    // vector<int> w = {-1, 2, 4};
    // vector<int> v = {-1, 100, 100};

    // 1. 枚举个数
    vector<vector<int>> f1(n + 1);
    for (int i = 0; i <= n; ++i)
        f1[i].resize(m + 1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (int k = 0; k <= c[i]; ++k)
            {
                if (j - k * w[i] >= 0)  // 未出界
                {
                    f1[i][j] = max(f1[i][j], f1[i - 1][j - k * w[i]] + k * v[i]);
                }
            }
        }
    }
    for_each(f1.begin(), f1.end(), [](vector<int>& inner) {
        for_each(inner.begin(), inner.end(), [](int ele) { cout << ele << "\t"; });
        cout << endl;
    });
    cout << "多重背包 : " << f1[n][m] << endl;
    cout << "----------------------------------" << endl;
    /*
        2. 对于物品i，总共可用c[i]个，例如13，我们可以将13分解为几个数字，使得1~13中
        每个数字都可以表示为这几个数字的简单和，例如13 = 1 + 2 + 4 + 6
        分解: 1, 2, 4, 2^(k-1), c[i]-2^k+1  k是满足c[i]+1 > 2^k的最大整数，
        例如c[i]=13, c[i]+1=14>2^k -> k=3，于是分解为1,2,4,6
        此时第三重循环从O(c[i])降低为O(log c[i])
     */

    vector<int> f(m + 1);

    auto ZeroOnePack = [&f, m](int weight, int value) {
        for (int j = m; j >= weight; --j)
            f[j] = max(f[j], f[j - weight] + value);
    };

    auto MultiplePack = [m, ZeroOnePack](int weight, int value, int quantity) {
        int t = 1;  // t = 2^k
        int bound = quantity + 1;
        while (t * 2 < bound)
        {
            ZeroOnePack(t * weight, t * value);  // 分解为指数的部分
            quantity -= t;
            t *= 2;
        }
        ZeroOnePack(quantity * weight, quantity * value);  // 不足指数的部分
    };
    for (int i = 1; i <= n; ++i)
        MultiplePack(w[i], v[i], c[i]);

    for_each(f.begin(), f.end(), [](int ele) { cout << ele << "\t"; });
    cout << endl;
    cout << "多重背包 : " << f[m] << endl;
    return 0;
}
