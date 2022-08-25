#include <stdio.h>
#include <string.h>

void reverse(char s[]);

void itob(unsigned int n, char s[], unsigned int b);

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

int main()
{
    unsigned int x = 0b110100101101;
    unsigned int y = 0b001110;
    unsigned int ans;

    char buffer_x[100];
    char buffer_y[100];
    char buffer_ans[100];

    int p = 4;
    ans = setbits(x, p, 3, y);

    itob(x, buffer_x, 2);
    itob(y, buffer_y, 2);
    itob(ans, buffer_ans, 2);

    printf("x:");

    for (int i = 0; i < p - 1; ++i)
        printf(" ");

    printf("%39s\n", buffer_x);
    printf("y: %39s\n", buffer_y);
    printf("ans: %37s\n", buffer_ans);

    return 0;
}

unsigned int getbits(unsigned int x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    unsigned int ans;
    unsigned int mask;

    mask = ~(~0 << n) & y;
    ans = (x >> (p + 1 - n)) | mask;
    mask = (~0 << n) | mask;
    ans &= mask;

    return ans;
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