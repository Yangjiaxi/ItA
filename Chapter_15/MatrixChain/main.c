#include <stdio.h>

#define N 6

/*
 * m[i, j] =
 * 0                                                if    i == j
 * min{m[i, k] + m[k+1, j] + p_{i-1} * p_k * p_j}   if    i < j, i<=k<j
 *
 * subproblem size increase w.r.t matrix chain length, from 2 to n
 */

void print_matrix_ans(int s[N][N + 1], int i, int j)
{
    if (i == j)
    {
        printf("{%d}", i);
    }
    else
    {
        printf("(");
        print_matrix_ans(s, i, s[i][j]);
        print_matrix_ans(s, s[i][j] + 1, j);
        printf(")");
    }
}

int main()
{
    // shape of matrix, for matrix A_i, 1 <= i <= n
    // size is (p_{i-1}, p_i), e.g.shape(A_1) = (30, 35)

    // int p[N + 1] = {30, 35, 15, 5, 10, 20, 25};   // N = 6
    // int p[N + 1] = {10, 100, 5, 50};              // N = 3
    int p[N + 1] = {5, 10, 3, 12, 5, 50, 6};  // N = 6

    // m[i, j] keeps the ans of A_i...A_j
    int m[N + 1][N + 1];
    // s[i, j] shows the split point for m[i, j]
    // split operator must perform on two or more matrices, so it is N * N-1
    int s[N][N + 1];
    for (int i = 1; i <= N; i++)
    {
        m[i][i] = 0;
    }
    for (int l = 2; l <= N; l++)  // length of matrix chain
    {
        for (int i = 1; i <= N - l + 1; i++)  // start point i
        {
            int j = i + l - 1;                // end point j
            m[i][j] = 0x3f3f3f3f;             // +inf
            for (int k = i; k <= j - 1; k++)  // split point k, i<=k<j
            {
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];  // dp
                if (m[i][j] > t)
                {
                    m[i][j] = t;
                    s[i][j] = k;  // record solution
                }
            }
        }
    }

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < i; j++)
        {
            printf("%8s", "");
        }
        for (int j = i + 1; j < N + 1; j++)
        {
            printf("%8d", m[i][j]);
        }
        printf("\n");
    }

    printf("Lowest Cost: %d\n", m[1][N]);

    printf("Solution:\n");
    print_matrix_ans(s, 1, N);  // print solution

    return 0;
}