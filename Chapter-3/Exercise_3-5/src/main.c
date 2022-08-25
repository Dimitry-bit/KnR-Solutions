/* Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s. */

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

void itob(unsigned int n, char s[], unsigned int b);

void reverse(char s[]);

int main()
{
    unsigned int num = 501;
    unsigned int base;
    char ans[MAX_LINE_LENGTH];

    base = 10;
    itob(num, ans, base);     // Base-10 (Decimal)
    printf("Base-%d: %s\n", base, ans);

    base = 2;
    itob(num, ans, base);      // Binary
    printf("Base-%d: %s\n", base, ans);

    base = 8;
    itob(num, ans, base);      // Octal
    printf("Base-%d: %s\n", base, ans);

    base = 16;
    itob(num, ans, base);     // Hexadecimal
    printf("Base-%d: %s\n", base, ans);

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

void itob(unsigned int n, char s[], unsigned int b)
{
    int i = 0;

    do
    {
        unsigned int reminder = n % b;

        if (b == 16 && reminder >= 10 && reminder <= 15)
            s[i++] = 'A' + (reminder - 10);
        else
            s[i++] = n % b + '0';

    } while (n /= b);

    s[i] = '\0';
    reverse(s);
}
