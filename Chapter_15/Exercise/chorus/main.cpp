#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::for_each;
using std::max;
using std::min;
using std::vector;

/*
    合唱队形问题:
        给出n个学生的身高，已排好，相对顺序不允许调整
        现在要构成一合唱队形，合唱队形以中间为分割点，左边严格上升，
        右边严格下降，现求最少多少名学生出队就可以构成一合唱队形

    输入:
        186 186 150 200 160 130 197 220
    输出:
        4
    解释:
        186 200 160 130
*/

/*
    DP:
        x[0..n-1] : x[i] 记录0..i的最长上升子序列长度
        y[0..n-1] : y[i] 记录0..i的最长下降子序列长度
        于是枚举所有中间节点i，x[i]+y[i]-1便是以i为中间节点时合唱队最多拥有的人数，用总人数减去则可得到出队人数
        LIS详见上级目录中LIS文件夹
*/

int main(int, char**)
{
    vector<int> h = {186, 186, 150, 200, 160, 130, 197, 220};
    int n = h.size();
    vector<int> x(n, 1);  // 上升序列
    vector<int> y(n, 1);  // 下降序列
    auto inv = [n](size_t idx) -> size_t { return n - 1 - idx; };
    int res = 0x3f3f3f3f;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (h[i] > h[j])
            {
                x[i] = max(x[i], x[j] + 1);
            }
            if (h[inv(i)] > h[inv(j)])
            {
                y[inv(i)] = max(y[inv(i)], y[inv(j)] + 1);
            }
        }
        res = min(res, n - (x[i] + y[i] - 1));
    }

    for_each(h.begin(), h.end(), [](int e) { cout << e << "\t"; });
    cout << endl;
    for_each(x.begin(), x.end(), [](int e) { cout << e << "\t"; });
    cout << endl;
    for_each(y.begin(), y.end(), [](int e) { cout << e << "\t"; });
    cout << endl;
    cout << "Minimal remove : " << res << " student(s)" << endl;
    return 0;
}
