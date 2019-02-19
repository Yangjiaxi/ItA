#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::vector;

/*
    01-背包问题：
        n个物品，m容量的背包，物品i重w[i]，价值v[i]
        向背包装入物品，使价值最大，输出价值
    e.g.
        n = 10, m = 67
        w = {-1, 23, 26, 20, 18, 32, 27, 29, 26, 30, 27}
        v = {-1, 505, 352, 458, 220, 354, 414, 498, 545, 473, 543}
        -1用作填充
        Output = 1270
*/

/*
    DP:
        let f[0..n][0..m] : f[i][j]保存用j的空间放置前i件物品时可以获得的最大价值

        f[0][k] = f[k][0] = 0 : 一件物品都不取/背包空间为0
        f[i][j] = max{f[i-1][j], f[i-1][j-c[i]]+w[i]}  For(i=1->n) For(j=1->m)
                      ----{1}--- -------{2}---------
        决策阶段：对于第i件物品，要 vs. 不要
        不要-1 : 由前i-1个物品的结果转移而来
        要-2 : 占用前i-1个物品的空间 + 第i个物品的价值
*/

int main(int, char**)
{
    int n = 10;
    int m = 67;
    vector<int> w = {-1, 23, 26, 20, 18, 32, 27, 29, 26, 30, 27};            // w[1..n]
    vector<int> v = {-1, 505, 352, 458, 220, 354, 414, 498, 545, 473, 543};  // v[1..n]

    // 1. 空间复杂度O(N*M)
    vector<vector<int>> f1(n + 1);
    for (int i = 0; i <= n; ++i)
        f1[i].resize(m + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (j >= w[i] && f1[i - 1][j - w[i]] + v[i] > f1[i - 1][j])
                f1[i][j] = f1[i - 1][j - w[i]] + v[i];
            else
                f1[i][j] = f1[i - 1][j];
        }
    }
    cout << "01-背包: " << f1[n][m] << endl;

    // 2. 空间复杂度O(M)
    /*
        思路：
            既然i递增，且递推式f[i][j] = max{f[i-1][j], f[i-1][j-c[i]]+w[i]}
            中的i行只由上一行转移来，且在更往后的运算中被计算过的行不会被二次修改，
            所以考虑只保存一行的结果，在原数组中重复使用
            于是考虑将递推式降维：f[j] = max{f[j], f[j-c[i]]+w[i]}
            这就要求我们在计算f[j]时，f[j-c[i]]不能先于f[j]被修改过，
            由于c[i]>0，所以j>j-c[i]，所以要从大向小推，于是递推式改写为
            f[j] = max{f[j], f[j-c[i]]+w[i]} For(i=1->n) For(j=m->1)
    */

    vector<int> f2(m + 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= w[i]; --j)
            f2[j] = max(f2[j], f2[j - w[i]] + v[i]);
    cout << "01-背包: " << f2[m] << endl;

    // 3. 打包，针对于一个物品
    vector<int> f3(m + 1, 0);
    auto Knapsack = [&f3, m](int weight, int value) {
        for (int v = m; v >= weight; --v)
            f3[v] = max(f3[v], f3[v - weight] + value);
    };
    for (int i = 1; i <= n; i++)
        Knapsack(w[i], v[i]);
    cout << "01-背包: " << f3[m] << endl;

    return 0;
}
