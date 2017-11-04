#include <stdio.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int main()
{
    int n;
    int arr[20];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        int key = i;
        for (int j = i + 1; j <= n; j++)
        {
            if (arr[j] < arr[key]) key = j;  //得到最小元素的下标
        }
        swap(&arr[key], &arr[i]);

    }

    for (int i = 1; i <= n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}