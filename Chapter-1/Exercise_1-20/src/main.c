/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
Should n be a variable or a symbolic parameter? */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define TAB_WIDTH 4

int get_line(char line[], int buffer_limit);

void string_format_to_space(const char line[], char line_formatted[], int buffer_limit, int tab_width);

int main()
{
    char line[MAX_LINE_LENGTH];
    char line_formatted[MAX_LINE_LENGTH];

    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        string_format_to_space(line, line_formatted, MAX_LINE_LENGTH, TAB_WIDTH);
        printf("%s", line_formatted);
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

void string_format_to_space(const char line[], char line_formatted[], int buffer_limit, int tab_width)
{
    int current_char;
    int pos = 0;
    int formatted_pos = 0;
    int column_char_count = 0;

    while ((current_char = line[pos++]) != '\0' && formatted_pos < buffer_limit - 1)
    {
        if (current_char == '\t')
        {
            while (column_char_count != tab_width && formatted_pos < buffer_limit - 1)
            {
                line_formatted[formatted_pos++] = ' ';
                ++column_char_count;
            }
        }
        else
        {
            line_formatted[formatted_pos++] = current_char;
            ++column_char_count;
        }

        if (column_char_count == tab_width)
            column_char_count = 0;
    }

    line_formatted[formatted_pos] = '\0';
}