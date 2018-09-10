#include <stdio.h>

int parent(int i)
{
	return i >> 1;
}

int left(int i)
{
	return i << 1;
}

int right(int i)
{
	return (i << 1) + 1;
}

typedef int (*HEAP);
int HEAP_SIZE;

void MAX_HEAPIFY(HEAP A, int i)
{
	int l = left(i);
	int r = right(i);
	int largest;

	if (l <= HEAP_SIZE && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r <= HEAP_SIZE && A[r] > A[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		int t = A[largest];
		A[largest] = A[i];
		A[i]       = t;
		MAX_HEAPIFY(A, largest);
	}
}

int main()
{
	int n;

	scanf("%d", &n);
	int A[n + 1];
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &A[i]);
	}
	HEAP_SIZE = n;
	MAX_HEAPIFY(A, 2);
	for (int i = 1; i <= HEAP_SIZE; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}
