/* Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
through 9, a through f, and A through F. */
#include <stdio.h>
#include <string.h>
#include <math.h>

int to_upper(char c);

unsigned long htoi(const char s[]);

int main()
{
    printf("%lu\n", htoi("0xFF"));
    return 0;
}

int to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
}

unsigned long htoi(const char s[])
{
    unsigned long sum = 0ul;
    unsigned int len;
    int i, current_char, power;
    int is_hex = 1;

    i = 0;
    len = strlen(s);
    if (len >= 2 && s[0] == '0' && to_upper(s[1]) == 'X')
        i = 2;

    // count from 0
    power = len - 1;
    while (i < len)
    {
        current_char = to_upper(s[i]);

        if (current_char >= 'A' && current_char <= 'F')
            current_char = current_char - 'A' + 10;
        else if (current_char >= '0' && current_char <= '9')
            current_char = current_char - '0';
        else
            is_hex = 0;

        sum += current_char * pow(16, power - i);
        ++i;
    }

    if (!is_hex)
        printf("error: Invalided input\n");

    return sum;
}

