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

void BUILD_MAX_HEAP(HEAP A, int size)
{
	HEAP_SIZE = size;
	for (int i = HEAP_SIZE >> 1; i >= 1; i--)
	{
		MAX_HEAPIFY(A, i);
	}
}

void HEAP_SORT(HEAP A, int size)
{
	BUILD_MAX_HEAP(A, size);
	for (int i = HEAP_SIZE; i >= 2; i--)
	{
		int t = A[1];
		A[1] = A[i];
		A[i] = t;
		HEAP_SIZE--;
		MAX_HEAPIFY(A, 1);
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
	HEAP_SORT(A, n);
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}
