#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
/*
    最优二叉搜索树构建问题：
    给出n个关键字与n+1个伪关键字，构建一棵最优二叉树T，使得平均搜索代价E[T]最小，
    E[T] := Sum{i=1->n, [depth(k_i)+1) * p_i]} + Sum{i=0->n, [depth(d_i)+1)*q_i]}
            -------------{Part.1}-------------   -----------{Part.2}-------------
          = 1 + Sum{i=1->n, depth(k_i)*p_i} + Sum{i=0->n, depth(d_i)*q_i}

          Part.1计算了关键字的搜索代价，Part.2计算伪关键字的搜索代价，二者合为总体代价

          其中:
            1. k_i构成关键字集合K，d_i构成伪关键字集合D
            2. p_i为关键字的出现频率，q_i为伪关键字的出现频率
            3. K集合不降序排列
            4. q_i对应的d_i位于k_i与k_{i+1}之间

    设：
        e[1..n+1][0..n] : e[i][j]记录关键字k_i到k_j的搜索代价
        w[1..n+1][0..n] : w[i][j]保存k_i...k_j的子树关键字概率和
            w[i][k] = Sum{k=i->j, p_k} + Sum{k=i-1->j, q_k}
        root[1..n+1][1..n+1] : 保存关键字k_i...k_j子树的根

    DP:
    e[i][j] :=  | q_{i-1}                                       if j = i -1
                | min{r=i->j, e[i][r-1] + e[r+1][j] + w[i][j]}  if i <= j

    算法效率: O(n^3)
*/

template <typename T>
void showMatrix(vector<vector<T>>& arr, int rb, int re, int cb, int ce, bool diag, string title)
{
    cout << "----------[" << title << "]-----------" << endl;
    for (int i = rb; i <= re; ++i)
    {
        for (int j = cb; j <= ce; ++j)
        {
            if (diag && !(j >= i - 1))
                cout << "\t";
            else
                cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void _rec_build_up(vector<vector<int>>& root,
                   int left,
                   int right,
                   int parent,
                   int dir)  // dir : 0->left, 1->right
{
    if (left > right)
        cout << "d" << right << "为k" << parent << "的" << ((dir == 0) ? "左" : "右") << "孩子"
             << endl;
    else
    {
        int rt = root[left][right];
        if (parent == 0)
            cout << "根为k" << rt << endl;
        else
            cout << "k" << rt << "为k" << parent << "的" << ((dir == 0) ? "左" : "右") << "孩子"
                 << endl;
        _rec_build_up(root, left, rt - 1, rt, 0);
        _rec_build_up(root, rt + 1, right, rt, 1);
    }
}
void bstBuildUp(vector<vector<int>>& root, int n)
{
    _rec_build_up(root, 1, n, 0, 0);
}

int main()
{
    int n = 5;
    vector<double> p = {0, 0.15, 0.10, 0.05, 0.10, 0.20};     // 1...n
    vector<double> q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};  // 0...n

    vector<vector<double>> e(n + 2);  // [1..n+1][0..n]
    for (int i = 0; i < e.size(); ++i)
        e[i].resize(n + 1);

    vector<vector<double>> w(n + 2);  // [1..n+1][0..n]
    for (int i = 0; i < w.size(); ++i)
        w[i].resize(n + 1);

    vector<vector<int>> root(n + 1);  // [1..n][1..n]
    for (int i = 0; i < root.size(); ++i)
        root[i].resize(n + 1);

    for (int i = 1; i <= n + 1; ++i)
        e[i][i - 1] = w[i][i - 1] = q[i - 1];

    int j;
    double t;
    for (int l = 1; l <= n; ++l)
    {
        for (int i = 1; i <= n - l + 1; ++i)
        {
            j = i + l - 1;
            e[i][j] = 0x3f3f3f3f;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; ++r)
            {
                t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    showMatrix(e, 1, n + 1, 0, n, true, "Matrix e");
    showMatrix(w, 1, n + 1, 0, n, true, "Matrix w");
    showMatrix(root, 1, n, 1, n, false, "Matix root");

    cout << endl << "Lowest cost : " << e[1][n] << endl << endl;

    bstBuildUp(root, n);
    return 0;
}
/*
----------[Matrix e]-----------
0.05    0.45    0.9     1.25    1.75    2.75
        0.1     0.4     0.7     1.2     2
                0.05    0.25    0.6     1.3
                        0.05    0.3     0.9
                                0.05    0.5
                                        0.1
----------[Matrix w]-----------
0.05    0.3     0.45    0.55    0.7     1
        0.1     0.25    0.35    0.5     0.8
                0.05    0.15    0.3     0.6
                        0.05    0.2     0.5
                                0.05    0.35
                                        0.1
----------[Matix root]-----------
1       1       2       2       2
0       2       2       2       4
0       0       3       4       5
0       0       0       4       5
0       0       0       0       5

Lowest cost : 2.75

根为k2
k1为k2的左孩子
d0为k1的左孩子
d1为k1的右孩子
k5为k2的右孩子
k4为k5的左孩子
k3为k4的左孩子
d2为k3的左孩子
d3为k3的右孩子
d4为k4的右孩子
d5为k5的右孩子
*/