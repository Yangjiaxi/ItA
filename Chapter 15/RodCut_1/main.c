#include <stdio.h>
#include <mem.h>

int f[20];
int a[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
int count;

/*
 * 钢条切割(Ver. function)
 * 状态:长度
 * 状态转移方程:
 *  f[l] = max(a[l],f[i]+f[l-i]) 1 <= i <= l
 */

int dp(int l)
{
  if (f[l])
  {
    return f[l];
  }
  else
  {
    int max = a[l];
    for (int i = 1; i <= l - 1; i++)
    {
      count++;
      if (max < dp(i) + dp(l - i))
        max = dp(i) + dp(l - i);
    }
    f[l] = max;
  }
}

int main()
{
  printf("length\tmax value\tcounting time(s)\n");
  for (int i = 1; i <= 10; i++)
  {
    count = 0;
    dp(i);
    printf("%d\t%d\t\t%d\n", i, f[i], count);
    memset(f, 0, sizeof(f));
  }
  return 0;
}