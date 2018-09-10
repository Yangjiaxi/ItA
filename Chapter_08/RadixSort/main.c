#include <stdio.h>
#include <windows.h>

int pow10(int p)
{
    int e = 1;
    for (int i = 1; i <= p; i++)
        e *= 10;
    return e;
}

int gen(int num, int d)
{
    int mod = pow10(d - 1);
    return (num / mod) % 10;
}

void COUNTING_SORT(int A[], int B[], int length, int d) //d: 第d位
{
    int C[20];

    for (int i = 0; i <= 9; i++)
        C[i] = 0;
    for (int j = 1; j <= length; j++)
    {
        C[gen(A[j], d)]++;
    }
    for (int i = 1; i <= 9; i++)
    {
        C[i] += C[i - 1];
    }
    for (int j = length; j >= 1; j--)
    {
        B[C[gen(A[j], d)]] = A[j];
        C[gen(A[j], d)]--;
    }
}

void swapArr(int a[], int b[], int n)
{
    //考虑使用memset,但memset的Big-O同样为n
    for (int i = 1; i <= n; i++)
    {
        a[i] = b[i];
        b[i] = 0;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n * 2]; //源数据
    int B[n * 2]; //保存结果
    int max = -1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &A[i]);
        if (max < A[i])
            max = A[i];
        B[i] = 0;
    }
    int d = 1;
    while (max /= 10)
        d++;
    for (int i = 1; i <= d; i++)
    {
        COUNTING_SORT(A, B, n, i);
        if (i < d)
            swapArr(A, B, n);
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", B[i]);
    printf("\n");
    system("PAUSE");
    return 0;
}
