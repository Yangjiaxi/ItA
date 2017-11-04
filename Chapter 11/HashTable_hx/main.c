#include <stdio.h>

#define HASHSIZE 20

int arr[20];

void hashCode(int key)
{
  int hash = 0;
  printf("%d->", key);
  while (key)
  {
    hash ^= ((hash << 5) + key % 10 + (hash >> 2));
    key /= 10;
  }
  hash %= 20;
  arr[hash]++;
  printf("%d\n", hash);
}

int main()
{
  for (int i = 1; i <= 100; i++)
  {
    hashCode(i);
  }
  int sum = 0;
  for (int i = 0; i < HASHSIZE; i++)
  {
    printf("HASH-TABLE%02d::%d:", i, arr[i]);
    sum += arr[i];
    for (int j = 1; j <= arr[i]; j++)
    {
      printf("#");
    }
    printf("\n");
  }
  printf("TOTAL:%d  SIZE:%d, AVE:%lf", sum, HASHSIZE, sum * 1.0 / HASHSIZE);

  return 0;
}