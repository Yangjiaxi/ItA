#include <iomanip>
#include <iostream>
#include <vector>
/*
    LCS-DP
    Given two string A and B, find the longest common subsequence C

    let matrix f(len(A) * len(B)),
    f[i ,j] specify len(LCS(prefix(A, i), prefix(B, j)))
        note: prefix(S, idx) takes idx-th prefix of S

    DP:
    ---------------------------------------------------
    f[i, j] =
        0                           i == 0 or j == 0
        f[i-1, j-1] + 1             A_i == B_j
        max{f[i, j-1], f[i-1, j]}   A_i != B_j
    for all 0<=i<=len(A),  0<=j<=len(B)
    ---------------------------------------------------
 */

enum dir
{
    DIAG,
    UP,
    LEFT,
    BOTH
};

void print_all_LCS(std::vector<std::vector<int>>& r,
                   std::string a,
                   std::string cur,
                   int max_len,
                   int i,
                   int j,
                   std::vector<std::string>& group,
                   bool allow_dep)
{
    if (!i || !j)
    {
        if (max_len == cur.length())
        {
            std::string res(cur);
            std::reverse(res.begin(), res.end());
            if (!allow_dep && std::find(group.begin(), group.end(), res) != group.end())
                return;
            group.push_back(res);
        }
        return;
    }
    switch (r[i][j])
    {
        case dir::UP:
            print_all_LCS(r, a, cur, max_len, i - 1, j, group, allow_dep);
            break;
        case dir::DIAG:
            cur += a[i - 1];
            print_all_LCS(r, a, cur, max_len, i - 1, j - 1, group, allow_dep);
            break;
        case dir::LEFT:
            print_all_LCS(r, a, cur, max_len, i, j - 1, group, allow_dep);
            break;
        case dir::BOTH:
            print_all_LCS(r, a, cur, max_len, i - 1, j, group, allow_dep);
            print_all_LCS(r, a, cur, max_len, i, j - 1, group, allow_dep);
            break;
    }
}

int main()
{
    std::string a = "ACCGGTCGAGATGCAG";
    std::string b = "GTCGTTCGGAATGCAT";
    // std::string a = "ABCBDAB";
    // std::string b = "BDCABA";
    int la = a.length();
    int lb = b.length();
    std::vector<std::vector<int>> f(la + 1, std::vector<int>(lb + 1, 0));
    std::vector<std::vector<int>> r(la + 1, std::vector<int>(lb + 1));

    for (int i = 1; i <= la; ++i)
    {
        for (int j = 1; j <= lb; ++j)
        {
            if (a[i - 1] == b[j - 1])
            {
                f[i][j] = f[i - 1][j - 1] + 1;
                r[i][j] = dir::DIAG;
            }
            else if (f[i - 1][j] > f[i][j - 1])
            {
                f[i][j] = f[i - 1][j];
                r[i][j] = dir::UP;
            }
            else if (f[i - 1][j] < f[i][j - 1])
            {
                f[i][j] = f[i][j - 1];
                r[i][j] = dir::LEFT;
            }
            else
            {
                f[i][j] = f[i][j - 1];
                r[i][j] = dir::BOTH;
            }
        }
    }

    int width = 3;
    std::cout << std::left << std::setw(width) << "";
    std::for_each(b.begin(), b.end(),
                  [&](const char el) { std::cout << std::left << std::setw(width) << el; });

    std::cout << std::endl;
    for (int i = 1; i <= la; ++i)
    {
        std::cout << std::left << std::setw(width) << a[i - 1];
        for (int j = 1; j <= lb; ++j)
            std::cout << std::left << std::setw(width) << f[i][j];
        std::cout << std::endl;
    }

    std::vector<std::string> res_group;

    print_all_LCS(r, a, "", f[la][lb], la, lb, res_group, false);

    std::cout << "{";

    for (size_t i = 0; i < res_group.size(); ++i)
    {
        if (i % 3 == 0)
            std::cout << std::endl << "    ";
        std::cout << res_group[i];
        if (i != res_group.size() - 1)
            std::cout << ", ";
    }

    std::cout << std::endl << "}" << std::endl;
    std::cout << "Total : " << res_group.size() << std::endl;
    return 0;
}