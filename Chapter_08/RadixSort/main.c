#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RadixSort.h"
#include "timer.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printf(
            "[ERROR] Argument length : %d, Expect for "
            ":\n\tBASE LENGTH MAX\n",
            argc);
        return 0;
    }
    int base = atoi(argv[1]);
    int size = atoi(argv[2]);
    int max = atoi(argv[3]);
    int min = 1;
    _TIME_INIT
    int* A = ArrRandInit(size, min, max);
    // PrintArray(A, size);
    _TIME_START
    int* B = RadixSort(A, size, base);
    _TIME_END
    // PrintArray(B, size);
    return 0;
}
