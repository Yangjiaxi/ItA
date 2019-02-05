#include <stdio.h>
#include <string.h>

void endl()
{
    printf("\n");
}

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

int main()
{
    // char* a = "AGGTAB";
    // char* b = "GXTXAYB";
    char* a = "ABCBDAB";
    char* b = "BDCABA";
    // char* a = "10010101";
    // char* b = "010110110";
    int la = strlen(a);
    int lb = strlen(b);
    int f[la + 1][lb + 1];
    int r[la + 1][lb + 1];

    for (int i = 0; i <= la; ++i)
    {
        for (int j = 0; j <= lb; ++j)
        {
            if (!i || !j)
                f[i][j] = 0;
            else if (a[i - 1] == b[j - 1])
            {
                f[i][j] = f[i - 1][j - 1] + 1;
                r[i][j] = 'd';  // diag
            }
            else if (f[i - 1][j] > f[i][j - 1])
            {
                f[i][j] = f[i - 1][j];
                r[i][j] = 'u';  // up
            }
            else
            {
                f[i][j] = f[i][j - 1];
                r[i][j] = 'l';  // left
            }
        }
    }

    printf("\t");
    for (int i = 0; i < lb; ++i)
    {
        printf("\t%c", b[i]);
    }

    endl();

    for (int i = 0; i <= la; ++i)
    {
        if (i)
            printf("%c", a[i - 1]);
        for (int j = 0; j <= lb; j++)
        {
            printf("\t%d", f[i][j]);
            if (i && j)
                printf("-%c", r[i][j]);
        }
        endl();
    }

    int i = la;
    int j = lb;
    char res[f[la][lb]];
    int idx = 0;
    while (i && j)
    {
        if (r[i][j] == 'd')
        {
            --i, --j;
            res[idx++] = a[i];
        }
        else if (r[i][j] == 'u')
            --i;
        else  // left
            --j;
    }

    endl();
    printf("LCS(%s, %s) = ", a, b);

    for (int i = idx - 1; i >= 0; --i)
    {
        printf("%c", res[i]);
    }
    endl();
    return 0;
}