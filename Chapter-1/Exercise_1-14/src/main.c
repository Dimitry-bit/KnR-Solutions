/* Exercise 1-14. Write a program to print a histogram of the frequencies of different characters
in its input. */

#include <stdio.h>

#define ASCII_PRINTABLE_CHAR_COUNT 94
#define ASCII_PRINTABLE_CHAR_START 33

int main()
{
    int c;
    int highest_frequency = 0;
    int ASCII_chars_array[ASCII_PRINTABLE_CHAR_COUNT];

    for (int i = 0; i < ASCII_PRINTABLE_CHAR_COUNT - 1; ++i)
        ASCII_chars_array[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (!(c >= 33 && c <= 126)) continue;

        ASCII_chars_array[c - ASCII_PRINTABLE_CHAR_START] += 1;
        if (ASCII_chars_array[c - ASCII_PRINTABLE_CHAR_START] > highest_frequency)
            highest_frequency = ASCII_chars_array[c - ASCII_PRINTABLE_CHAR_START];
    }

    for (int y = highest_frequency; y > 0; --y)
    {
        printf("%4d |", y);
        for (int i = 0; i < ASCII_PRINTABLE_CHAR_COUNT - 1; ++i)
        {
            if (ASCII_chars_array[i] == 0) continue;

            if (ASCII_chars_array[i] >= y)
                printf("*");
            else
                printf(" ");

            printf(" ");
        }
        printf("\n");
    }

    printf("     +");
    for (int i = 0; i < ASCII_PRINTABLE_CHAR_COUNT - 1; ++i)
    {
        if (ASCII_chars_array[i] != 0)
            printf("--");
    }
    printf("\n");

    printf("      ");
    for (int i = 0; i < ASCII_PRINTABLE_CHAR_COUNT - 1; ++i)
    {
        if (ASCII_chars_array[i] != 0)
            printf("%c ", i + ASCII_PRINTABLE_CHAR_START);
    }
    printf("\n");

    return 0;
}
