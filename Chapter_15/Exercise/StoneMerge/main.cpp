#include <iostream>
#include <vector>

/*
    石子合并问题
    n个石子排成一圈，每次选择相邻的两堆进行合并，合并得分为原两堆的和，
    并将新的一堆的石子数记为合并得分，问最最终能获得的最大与最小总得分
    例如:
    n=4, a = {4, 4, 5, 9}
    ->(顺时针一圈)
        4
      9   4
        5
    res:
        min=43, max=54
    解释:
        4 4 5 9 -> 8 5 9 -> 13 9 -> 22
        score = 8 + 13 + 22 = 43
        4 4 5 9 -> 4 4 14 -> 4 18 -> 22
        score = 14 + 18 + 22 = 54
*/

/*
    DP:
    let f[1..n][1..n] : f[i][j]记录从第i堆起顺时针合并j堆所取得的最大得分
    显然f[k][1] = 0，边界条件
    考虑f[i][j]，可以分解为子问题：
        从第i堆起合并j堆，需要在i,i+1,i+2,...,i+j-1堆中寻找切分点k(1<=k<=j-1)，
        分别为前k堆和后j-k堆，于是构成子问题f[i][k]+f[i+k][j-k]，
        子问题的合并收益为Sum(k=i->j, a_k)
    let sum[1..n][1..n] : sum[i][j]记录从第i堆起j堆石子的总和，目的是后续方便查表

    于是f[i][j] = Max(k=1->j-1, f[i][k]+f[i+k][j-k]+sum[i][j])
    最小值同理
*/

int main()
{
    int n = 4;
    std::vector<int> a = {-1, 4, 4, 5, 9};  // -1为占位符

    std::vector<std::vector<int>> f_max(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> f_min(n + 1, std::vector<int>(n + 1, 0x3f3f3f3f));

    std::vector<std::vector<int>> sum(n + 1, std::vector<int>(n + 1, 0));

    auto cir = [n](int i) { return (i + n - 1) % n + 1; };

    for (int i = 1; i <= n; ++i)
    {
        sum[i][1] = a[i];
        f_min[i][1] = 0;
        for (int j = 2; j <= n; ++j)
            sum[i][j] = sum[i][j - 1] + a[cir(i + j - 1)];
    }

    for (int j = 2; j <= n; ++j)  // 合并堆数
    {
        for (int i = 1; i <= n; ++i)  // 起始位置
        {
            for (int k = 1; k <= j - 1; ++k)  // 合并位置
            {
                f_max[i][j] =
                    std::max(f_max[i][j], f_max[i][k] + f_max[cir(i + k)][j - k] + sum[i][j]);
                f_min[i][j] =
                    std::min(f_min[i][j], f_min[i][k] + f_min[cir(i + k)][j - k] + sum[i][j]);
            }
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            std::cout << f_max[i][j] << "(" << f_min[i][j] << ")"
                      << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "Max : " << f_max[1][n] << std::endl << "Min : " << f_min[1][n] << std::endl;
    return 0;
}
