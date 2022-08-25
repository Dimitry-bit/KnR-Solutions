// Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||.
#include <stdio.h>

#define MAX_LINE 1000

int getline_l(char s[], int lim);

int main()
{
    int len;
    char line[MAX_LINE];

    while ((len = getline_l(line, MAX_LINE)) > 0)
        printf("%s :%d\n", line, len);

    return 0;
}

int getline_l(char s[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1; ++i)
    {
        if ((c = getchar()) == EOF || c == '\n')
        {
            s[i] = '\0';
            break;
        }

        s[i] = c;
    }

    return i;
}