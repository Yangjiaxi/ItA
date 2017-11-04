#include <stdio.h>
#include<malloc.h>
int main()
{
	int n, key, j;
	scanf("%d",&n);
	int *arr = (int *)malloc(sizeof(int) * (n+1));
	for(int i = 0; i < n; i++) scanf("%d",(arr+i));
	for(int i = 1; i < n; i++)
	{
		key = *(arr + i);
		j = i - 1;
		while(j >= 0 &&  *(arr + j) > key)
		{
			*(arr + j + 1) = *(arr + j);
			j--;
		}
		arr[j+1] = key;
	}
	for(int i = 0; i < n; i++) printf("%d ",*(arr + i));
	printf("\n");
	return 0;
}
