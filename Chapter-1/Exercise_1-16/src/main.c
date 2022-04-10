/* Exercise 1-16. Revise the main routine of the longest-line program so it will correctly print
the length of arbitrary long input lines, and as much as possible of the text. */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int get_line(char line[], int buffer_limit);

void string_copy(char to[], const char from[]);

int main()
{
    int current_line_length;
    int longest_line_length;
    char line[MAX_LINE_LENGTH];
    char longest_line[MAX_LINE_LENGTH];

    longest_line_length = 0;
    while ((current_line_length = get_line(line, MAX_LINE_LENGTH)) > 0)
    {
        if (current_line_length > longest_line_length)
        {
            longest_line_length = current_line_length;
            string_copy(longest_line, line);
        }

        if (current_line_length == MAX_LINE_LENGTH - 1 && line[current_line_length - 1] != '\n')
        {
            int c;
            while ((c = getchar()) != EOF && c != '\n')
                ++current_line_length;

            longest_line_length = current_line_length;
        }
    }

    if (longest_line_length > (MAX_LINE_LENGTH - 1))
        printf("Storage limit exceeded by: %d\n", longest_line_length - (MAX_LINE_LENGTH - 1));

    if (longest_line_length > 0)
    {
        printf("LENGTH: %d\n", longest_line_length);
        printf("\n");
        printf("%s", longest_line);
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

void string_copy(char to[], const char from[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        i++;
}