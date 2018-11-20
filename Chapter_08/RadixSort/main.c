#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void counting_sort(int A[], int B[], int length, int d) //d: 第d位
{
    int C[10];

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

void swap_arr(int a[], int b[], int n)
{
    //考虑使用memset,但memset的Big-O同样为n
    for (int i = 1; i <= n; i++)
    {
        a[i] = b[i];
        b[i] = 0;
    }
}

int *rand_arr(int size, int max_n)
{
    srand(time(NULL));
    int *a = malloc(sizeof(int) * (size + 1));
    for (int i = 1; i <= size; i++)
    {
        a[i] = rand() % max_n;
    }
    return a;
}

int main()
{
    int n = 10;
    int max = -1;
    int *A = rand_arr(n, 500);
    int *B = malloc(sizeof(int) * (n + 1));
    int d = 1;
    printf("Ori data: ");
    for (int i = 1; i <= n; i++)
    {
        if (max < A[i])
            max = A[i];
        printf("%10d", A[i]);
    }
    printf("\n");
    while (max /= 10)
    {
        d++;
    }
    for (int i = 1; i <= d; i++)
    {
        counting_sort(A, B, n, i);
        printf("step %02d : ", i);
        for (int i = 1; i <= n; i++)
            printf("%10d", B[i]);
        if (i < d)
            swap_arr(A, B, n);
        printf("\n");
    }

    return 0;
}
