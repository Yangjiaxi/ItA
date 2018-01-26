#include <stdio.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int PARTITION(int a[], int left, int right)
{
    int key = a[right];
    //i表示比关键字小的最后一个元素下标
    //j表示比关键字大的最后一个元素下标
    int i = left - 1;
    //j从待排序区第一个元素(left)遍历到关键字之前的元素(right - 1)
    for (int j = left; j <= right - 1; j++)
    {
        //如果j指向的元素比关键字小，则把他与j区第一个元素swap，并i++，这一过程把该元素移入i区，并更新i的大小
        if (a[j] <= key) //排序关，修改为>=可实现升序排列
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[right]); //这时数组模型：[比Key小][比Key大]Key --交换--> [比Key小]Key[比Key大]
    return i + 1;               //i保存的是比关键字小的最后一个元素的下标，故i+1表示key的位置，下一次递归进行[left,i-1]和[i+1,right]的排序
}

void QUICK_SORT(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = PARTITION(a, left, right);
        QUICK_SORT(a, left, mid - 1);
        QUICK_SORT(a, mid + 1, right);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    QUICK_SORT(a, 1, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
