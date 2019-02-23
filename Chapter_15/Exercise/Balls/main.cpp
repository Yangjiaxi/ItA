#include <iostream>
#include <vector>

/*
    传球游戏：
        n个人围成一圈，从第一个人开始传球，球只能传给
        身边的两个人，问在m次传球后，球有多少种可能的路径
        再次回到第一个人手里
    例如：
        n=3, m=3
        1.2.1.2
             .3
           .3.1 <-
             .2
         .3.1.2
           .2.1 <-
        结果: 2
*/

/*
    DP:
    let f[1..m][1..n] : f[i][j]记录i次传球后落入j号人手中的可能方案数
    f[0][1] = 1 (初始情况)
    对于j号，可以由其左右两人传来，于是
    f[i][j] = f[i-1][left(j)] + f[i-1][right(j)]
    其中left与right处理j=1/n的情况
    j=1, left(j)=n, right(j)=2
    j=n, left(j)=n-1, right(j)=1
*/
int main(int, char**)
{
    uint n = 3;
    uint m = 3;
    std::vector<std::vector<uint>> f(m + 1, std::vector<uint>(n + 1, 0));

    auto left = [n](const uint j) -> uint { return (j == 1) ? n : j - 1; };
    auto right = [n](const uint j) -> uint { return (j == n) ? 1 : j + 1; };

    f[0][1] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            f[i][j] = f[i - 1][left(j)] + f[i - 1][right(j)];

    std::cout << f[m][1] << std::endl;
    return 0;
}
