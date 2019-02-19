#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
    数的统计：
        给定自然数n，按照以下方法处理
        1. 不处理
        2. 左边加上一个数，该数不能超过最左边的数的一半
        3. 重复1,2直到不能添加任何数字
        注意：自然数从1开始定义
    例如：
        (1) 输入：6
            输出：6
            解释：6,16,26,126,36,136
        (2) 输入：10
            输出：14
            解释：10,110,210,1210,310,1310,410,1410,2410,12410,510,1510,2510,12510
    要求：
        输入n，输出可生成的自然数的个数
*/

/*
    DP:
        f[1] = 1
        f[n] = 1 + Sum(k=1->n/2, f[k])
*/

int _dp_rec(int n, vector<int>& arr)
{
    if (arr[n] == 0)
    {
        arr[n] = 1;
        for (int i = 1; i <= n / 2; ++i)
        {
            arr[n] += _dp_rec(i, arr);
        }
    }
    cout << "f[" << n << "] = " << arr[n] << endl;
    return arr[n];
}

int dp_rec(int n)
{
    vector<int> arr(n + 1, 0);
    return _dp_rec(n, arr);
}

int dp_iter(int n)
{
    vector<int> arr(n + 1, 1);
    arr[0] = 0;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= i / 2; ++j)
        {
            arr[i] += arr[j];
        }
    }
    return arr[n];
}

int main(int, char**)
{
    int n = 10;
    cout << "count(" << n << ") = " << dp_rec(n) << endl;
    cout << "count(" << n << ") = " << dp_iter(n) << endl;
    return 0;
}
