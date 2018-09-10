#include <stdio.h>
#include <conio.h>

void COUNTING_SORT(int *A, int *B, int k, int length)
{
    int C[k];

    for (int i = 0; i <= k; i++)
        C[i] = 0;
    for (int j = 1; j <= length; j++)
        C[A[j]]++; //利用数组下标表示元素

    for (int i = 1; i <= k; i++)
        C[i] += C[i - 1]; //每个数组元素表示不大于该元素下标的元素的数目

    for (int j = length; j >= 1; j--)
    {
        B[C[A[j]]] = A[j]; // C[A[j]]
                           // 表示不大于这个元素的元素的数目，故这个元素的排位就是C[A[j]]
        C[A[j]]--;         //用来维护重复数据的位置
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n + 1]; //源数据
    int B[n + 1]; //保存结果
    int max = -1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &A[i]);
        if (A[i] > max)
            max = A[i];
        B[i] = 0;
    }
    COUNTING_SORT(A, B, max, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", B[i]);
    printf("\n");
    getch();
    return 0;
}
