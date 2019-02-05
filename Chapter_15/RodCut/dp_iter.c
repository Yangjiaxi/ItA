#include <stdio.h>

#define N 10

int dp_iter(int* cost, int n);

/*
 *  f[l] = max(a[l],f[i]+f[l-i]) 1 <= i <= l
 */

int dp_iter(int* cost, int n)
{
    int result[n + 1];
    int record[n + 1];
    result[0] = 0;
    for (int j = 1; j <= n; ++j)
    {
        int q = -1;
        for (int i = 1; i <= j; ++i)
        {
            if (q < cost[i] + result[j - i])
            {
                q = cost[i] + result[j - i];
                record[j] = i;
            }
        }
        result[j] = q;
    }
    printf("%d = ", n);
    int rn = n;
    while (rn)
    {
        printf("%d", record[rn]);
        rn -= record[rn];
        if (rn > 0)
            printf(" + ");
        else
            printf("\n");
    }
    return result[n];
}

int main()
{
    int cost[N + 1] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    for (int target = 1; target <= 10; ++target)
    {
        printf("cost : %d\n", dp_iter(cost, target));
        printf("--------------------------------\n");
    }
    return 0;
}