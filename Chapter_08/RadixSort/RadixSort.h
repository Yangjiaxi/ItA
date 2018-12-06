#define max(a, b) (((a) > (b)) ? (a) : (b))

// 桶式排序算法，将数组A中数据在base进制下的第digit位排序，存入数组B
void BucketSort(int* A, int* B, int size, int digit, int base);
// 基数排序算法，将数组A中的size个数据按照base进制排序，返回指向排序后数组的指针
int* RadixSort(int* A, int size, int base);
// 随机初始化int数组，大小size，[left, right]，最后一个元素一定为right
int* ArrRandInit(int size, int left, int right);
// 输出长度为size的数组Arr
void PrintArray(int* Arr, int size);
// 返回初始化为0的size长度的数组
int* MakeEmptyArray(int size);
