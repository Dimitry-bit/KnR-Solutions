/* Exercise 1-17. Write a program to print all input lines that are longer than 80 characters. */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int get_line(char line[], int buffer_limit);

int main()
{
    int current_line_length;
    char line[MAX_LINE_LENGTH];

    while ((current_line_length = get_line(line, MAX_LINE_LENGTH)) > 0)
    {
        if (current_line_length == MAX_LINE_LENGTH - 1 && line[current_line_length - 1] != '\n')
        {
            int c;
            while ((c = getchar()) != EOF && c != '\n')
                ++current_line_length;
        }

        if (current_line_length > (MAX_LINE_LENGTH - 1))
            printf("Storage limit exceeded by: %d\n", current_line_length - (MAX_LINE_LENGTH - 1));

        if (current_line_length > 80)
        {
            printf("LENGTH: %d\n", current_line_length);

            if (line[current_line_length - 1] != '\n')
                printf("%s\n", line);
            else
                printf("%s", line);

            printf("\n");
        }
    }

    return 0;
}

int get_line(char line[], int buffer_limit)
{
    int c;
    int i;

    for (i = 0; i < buffer_limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n')
    {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i;
}