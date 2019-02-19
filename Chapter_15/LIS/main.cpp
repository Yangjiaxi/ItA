#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::distance;
using std::endl;
using std::for_each;
using std::max;
using std::max_element;
using std::setw;
using std::stack;
using std::vector;

#define WIDTH 4

int main()
{
    vector<int> arr = {10, 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    // vector<int> arr = {1, 2, 3, 4, 5, 6, 4, 4, 4, 4, 4, 4};
    vector<int> f(arr.size(), 1);
    vector<int> prev(arr.size(), -1);
    for (int i = 1; i < arr.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (arr[i] >= arr[j])
            {
                int t = f[j] + 1;
                if (t > f[i])
                {
                    f[i] = t;
                    prev[i] = j;
                }
            }
        }
    }
    cout << "index";
    for (int i = 0; i < arr.size(); ++i)
        cout << setw(WIDTH) << i;
    cout << endl << "array";
    for_each(arr.begin(), arr.end(), [](const int ele) { cout << setw(WIDTH) << ele; });
    cout << endl << "table";
    for_each(f.begin(), f.end(), [](const int ele) { cout << setw(WIDTH) << ele; });
    cout << endl << " prev";
    for_each(prev.begin(), prev.end(), [](const int ele) { cout << setw(WIDTH) << ele; });
    cout << endl;

    stack<int> stk;
    long idx = max_element(f.begin(), f.end()) - f.begin();
    while (idx != -1)
    {
        stk.push(arr[idx]);
        idx = prev[idx];
    }
    cout << "  res";
    while (!stk.empty())
    {
        cout << setw(WIDTH) << stk.top();
        stk.pop();
    }
    cout << endl;
    return 0;
}
/*
index   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
array  10   0   8   4  12   2  10   6  14   1   9   5  13   3  11   7  15
table   1   1   2   2   3   2   3   3   4   2   4   3   5   3   5   4   6
 prev  -1  -1   1   1   2   1   2   3   4   1   7   3  10   5  10   7  12
  res   0   4   6   9  13  15
*/