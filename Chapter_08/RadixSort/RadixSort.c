#include "RadixSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int BasePow(int base, int t)
{
    int e = 1;
    for (int i = 1; i <= t; i++)
        e *= base;
    return e;
}

int gen(int num, int d, int base)
{
    int mod = BasePow(base, d - 1);
    return (num / mod) % base;
}

void SwapArr(int* A, int* B, int n)
{
    for (int i = 0; i < n; i++)
    {
        A[i] = B[i];
        B[i] = 0;
    }
}

int* ArrRandInit(int size, int left, int right)
{
    srand(time(NULL));
    int* a = malloc(sizeof(int) * size);
    for (int i = 0; i < size - 1; i++)
    {
        a[i] = rand() % (right - left + 1) + left;
    }
    a[size - 1] = right;
    return a;
}

int* MakeEmptyArray(int size)
{
    int* a = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        a[i] = 0;
    }
    return a;
}

void PrintArray(int* Arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", Arr[i]);
    }
    printf("\n");
}

void BucketSort(int* A, int* B, int size, int digit, int base)
{
    int C[base];

    for (int i = 0; i <= base - 1; i++)
        C[i] = 0;

    for (int i = 0; i < size; i++)
        C[gen(A[i], digit, base)]++;

    for (int i = 1; i <= base - 1; i++)
        C[i] += C[i - 1];

    // 因为原始数组中低一位已经升序排好
    // 所以较大但高位相同的元素应当提前进入数组
    for (int i = size - 1; i >= 0; i--)
    {
        int tmp = gen(A[i], digit, base);
        B[C[tmp] - 1] = A[i];
        C[tmp]--;
    }
}

int* RadixSort(int* A, int size, int base)
{
    int d = 1;
    int max = -1;
    int* B = MakeEmptyArray(size);
    for (int i = 0; i < size; i++)
    {
        if (max < A[i])
            max = A[i];
    }
    while (max /= base)
        ++d;
    for (int i = 1; i <= d; i++)
    {
        BucketSort(A, B, size, i, base);
        if (i < d)
        {
            SwapArr(A, B, size);
        }
    }
    return B;
}
