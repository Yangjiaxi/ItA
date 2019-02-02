#include <stdio.h>
#include <stdlib.h>

#define N 10
#define max(a, b) (a) > (b) ? (a) : (b)

int dp_rec(int* cost, int n);
int dp_rec_aux(int* cost, int* res, int n);

/*
 *  f[l] = max(a[l],f[i]+f[l-i]) 1 <= i <= l
 */

int dp_rec(int* cost, int n)
{
    int* res = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++)
    {
        res[i] = -1;
    }
    res[0] = 0;
    int ans = dp_rec_aux(cost, res, n);
    free(res);
    return ans;
}

int dp_rec_aux(int* cost, int* res, int n)
{
    if (res[n] >= 0)
        return res[n];

    int q = -1;
    for (int i = 1; i <= n; i++)
    {
        q = max(q, cost[i] + dp_rec_aux(cost, res, n - i));
    }

    res[n] = q;
    return q;
}

int main()
{
    int cost[N + 1] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int query = 4;
    printf("%d\n", dp_rec(cost, query));
    return 0;
}