/* Exercise 3-4. In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs. */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

void reverse(char s[]);

void itoa(int n, char s[]);

int main()
{
    int int_test1 = INT32_MIN;
    char ans_array[MAX_LINE_LENGTH];
    itoa(int_test1, ans_array);
    printf("number: %d\nnumber_s: %s", int_test1, ans_array);
    return 0;
}

void reverse(char s[])
{
    int c;

    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    sign = n;

    i = 0;
    do
        s[i++] = abs(n % 10) + '0';
    while ((n /= 10));        /* delete it */

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
