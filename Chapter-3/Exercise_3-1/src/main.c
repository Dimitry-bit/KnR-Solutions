/* Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop and
measure the difference in run-time. */

#include <stdio.h>

#define ARRAY_SIZE 10

int binsearch(int x, int v[], int n);

int main()
{
    int test_array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int x = 9;

    printf("Value: %d Location: %d\n", x, binsearch(x, test_array, ARRAY_SIZE));
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid])
    {
        mid = (low + high) / 2;

        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return x == v[mid] ? mid : -1;
}
