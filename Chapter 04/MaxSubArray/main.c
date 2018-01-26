#include <stdio.h>
#include <limits.h>

/*
 * 寻找数组A[1...n]的最大的连续子数组(数组内有负数元素)
 * 最大连续子数组一定存在于三个位置
 *  1.[1,mid]内
 *  2.[mid+1,n]内
 *  3.跨越mid下标
 * 而在这三个子数组中，最大子数组同样处于这三个位置
 * 所以使用分治策略
 *  1.先找出[left, mid]的最大子数组
 *  2.再找出[mid+1, right]的最大子数组
 *  3.最后找出跨越mid的最大子数组
 *  4.比较三个子数组，找出结果最大的一个，返回
 */

typedef struct _Data
{
  int left;
  int right;
  int value;
} Data;

Data findCross(const int *A, int left, int mid, int right)
{
  Data val;
  //find left with mid
  int leftSum = INT_MIN;
  int sum = 0;
  val.left = mid;
  for (int i = mid; i >= left; i--)
  {
    sum += A[i];
    if (sum > leftSum)
    {
      leftSum = sum;
      val.left = i;
    }
  }
  //find right with mid+1
  int rightSum = INT_MIN;
  sum = 0;
  val.right = mid + 1;
  for (int i = mid + 1; i <= right; i++)
  {
    sum += A[i];
    if (sum > rightSum)
    {
      rightSum = sum;
      val.right = i;
    }
  }
  val.value = leftSum + rightSum;
  return val;
}

Data maxVal(Data a, Data b, Data c)
{
  if (a.value >= b.value && a.value >= c.value) return a;
  else if (b.value >= a.value && b.value >= c.value) return b;
  else return c;
}

Data findMaxSubArray(const int *A, int left, int right)
{
  Data res;
  if (left == right)
  {
    res.left = res.right = left;
    res.value = A[left];
  }
  else
  {
    int mid = (left + right) >> 1;
    Data leftVal = findMaxSubArray(A, left, mid);
    Data rightVal = findMaxSubArray(A, mid + 1, right);
    Data crossVal = findCross(A, left, mid, right);
    res = maxVal(leftVal, rightVal, crossVal);
  }
  return res;
}

int main()
{
  int n;
  scanf("%d", &n);
  int A[n + 1];
  for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
  Data res = findMaxSubArray(A, 1, n);
  printf("%d  %d  %d\n", res.left, res.right, res.value);
  return 0;
}