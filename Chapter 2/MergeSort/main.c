#include <stdio.h>

void merge(int *a, int begin, int mid, int end)
{
    int n1 = mid - begin + 1;
    int n2 = end - mid;
    int left[n1];
    int right[n2];
    for (int i = begin, j = 0; j < n1; j++, i++) left[j] = a[i];
    for (int i = mid + 1, j = 0; j < n2; j++, i++) right[j] = a[i];
    int i, j;
    i = j = 0;
    int k = begin;
    //i->left->n1   j->right->n2
    while ((i < n1) && (j < n2))
    {
        if (left[i] < right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }
    while (i < n1) a[k++] = left[i++];
    while (j < n2) a[k++] = right[j++];
}

//end is the last index of element, NOT the "After End" one
void merge_sort(int *a, int begin, int end)
{
    if (begin < end)
    {
        int mid = (begin + end) / 2;
        merge_sort(a, begin, mid);
        merge_sort(a, mid + 1, end);
        merge(a, begin, mid, end);
        //in the arr "a", Part[begin..mid] and Part[mid+1...end] are both sorted, just merge them
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n + 1];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}