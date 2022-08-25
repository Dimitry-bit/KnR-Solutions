/* Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally. */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define SAMPLE_SIZE 13
#define MAX_LINE_SIZE 1000

void expand(const char s1[], char s2[]);

bool is_same_format(char c1, char c2);

int main()
{
    char s[MAX_LINE_SIZE];
    char sample[SAMPLE_SIZE][MAX_LINE_SIZE] =
            {
                    "0-9",
                    "-0-9",
                    "a-z",
                    "a-z-",
                    "-a-z",
                    "-a-b-c",
                    "a-b-c",
                    "a-z0-9",
                    "a-z-0-9",
                    "0--9",
                    "A-z",
                    "0-z",
                    "0-"
            };

    for (int i = 0; i < SAMPLE_SIZE; ++i)
    {
        expand(sample[i], s);
        printf("%s\n", s);
    }

    return 0;
}

bool is_same_format(char c1, char c2)
{
    return islower(c1) && islower(c2) || isupper(c1) && isupper(c2) || isdigit(c1) && isdigit(c2);
}

void expand(const char s1[], char s2[])
{
    int j;
    char prevChar = 0;
    bool isWildCard = false;

    j = 0;
    for (int i = 0; s1[i] != '\0'; ++i)
    {
        if (s1[i] == '-' && !isWildCard)
        {
            isWildCard = true;
            continue;
        }

        int diff = s1[i] - (prevChar + 1);
        if (isWildCard && prevChar && is_same_format(prevChar, s1[i]) && diff > 0)
        {
            isWildCard = false;

            for (int k = 0; k <= diff; ++k)
                s2[j++] = (prevChar + 1) + k;
        }
        else
        {
            if (isWildCard)
            {
                isWildCard = false;
                s2[j++] = '-';
            }

            s2[j++] = s1[i];
            prevChar = s1[i];
        }
    }

    if (isWildCard)
        s2[j++] = '-';

    s2[j] = '\0';
}