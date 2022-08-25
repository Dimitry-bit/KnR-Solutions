/* Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with blanks on the
left if necessary to make it wide enough. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

void reverse(char s[]);

void itoa(int n, char s[], int w);

int main()
{
    char ans[MAX_LINE_LENGTH];

    itoa(50, ans, 4);
    printf("Ans:\"%s\"\n", ans);

    itoa(-50, ans, 4);
    printf("Ans:\"%s\"\n", ans);

    itoa(50, ans, -4);
    printf("Ans:\"%s\"\n", ans);

    itoa(50, ans, 0);
    printf("Ans:\"%s\"\n", ans);
    return 0;
}

void reverse(char s[])
{
    int c;

    for (int i = 0, j = strlen(s) - 1; i < j; ++i, --j)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[], int w)
{
    int i = 0;
    int sign = n;

    do
    {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);

    if (sign < 0)
        s[i++] = '-';

    if (w < 0)      // Left Justified
    {
        s[i] = '\0';
        reverse(s);
    }

    int padding = abs(w) - (i);
    while (padding > 0)
    {
        s[i++] = ' ';
        --padding;
    }

    if (w >= 0)     // Right Justified
    {

        s[i] = '\0';
        reverse(s);
    }
}