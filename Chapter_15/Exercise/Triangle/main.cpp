#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::max;
using std::max_element;
using std::ofstream;
using std::vector;

/*
    区间型动态规划：数字三角形
    例如：
        n = 5
        7
        3   8
        8   1   0
        2   7   4   4
        4   5   2   6   5
    从7出发，每次只能向下或向右下，收益为沿途经过的数字和，求最大收益
    f[1..n][1..n] : f[i][j] 到达f[i][j]时所能获得的最大收益
    f[i][j] = max(f[i-1][j], f[i-1][j-1])

*/

int main()
{
    ifstream input("input.txt");
    if (!input.is_open())
    {
        std::cerr << "[ERROR] Open with an error, check file named [input.txt]" << endl;
        exit(-1);
    }

    int n;
    input >> n;  // 5
    vector<vector<int>> a(n + 1);
    vector<vector<int>> f(n + 1);

    for (int i = 0; i <= n; ++i)
    {
        a[i].resize(n + 1);
        f[i].resize(n + 1);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            input >> a[i][j];
    input.close();

    // 1. 从上向下顺推

    /* {begin : core_1} */
    f[1][1] = a[1][1];
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + a[i][j];
    /* {end : core_1} */

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
            cout << f[i][j] << "\t";
        cout << endl;
    }
    cout << "最高价值 : " << *max_element(f[n].begin(), f[n].end()) << endl;

    cout << "----------------------------------------" << endl;

    // 2. 从下向上逆推
    vector<vector<int>> r(n + 1);  // 记录决策

    for (int i = 0; i <= n; ++i)
    {
        f[i].clear();
        f[i].resize(n + 1);
        r[i].resize(n + 1);
    }

    /* {begin : core_2} */
    for (int i = 1; i <= n; ++i)
        f[n][i] = a[n][i];
    for (int i = n - 1; i >= 1; --i)
        for (int j = 1; j <= i; ++j)
        {
            if (f[i + 1][j] > f[i + 1][j + 1])
            {
                f[i][j] = f[i + 1][j] + a[i][j];
                r[i][j] = 0;
            }
            else
            {
                f[i][j] = f[i + 1][j + 1] + a[i][j];
                r[i][j] = 1;
            }
        }
    /* {end : core_2} */

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
            cout << f[i][j] << "\t";
        cout << endl;
    }
    cout << "决策记录: " << endl;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
            cout << (r[i][j] == 0 ? "↓" : "↘") << " ";
        cout << endl;
    }

    cout << "最高价值 : " << f[1][1] << " = ";
    int idx = 1;
    for (int i = 1; i <= n; ++i)
    {
        cout << a[i][idx];
        if (i < n)
        {
            idx += r[i][idx];
            cout << " + ";
        }
    }
    cout << endl;

    return 0;
}

/*
7
10      15
18      16      15
20      25      20      19
24      30      27      26      24
最高价值 : 30
----------------------------------------
30
23      21
20      13      10
7       12      10      10
4       5       2       6       5
决策记录:
↓
↓ ↓
↘ ↓ ↘
↘ ↓ ↘ ↓
↓ ↓ ↓ ↓ ↓
最高价值 : 30 = 7 + 3 + 8 + 7 + 5
*/