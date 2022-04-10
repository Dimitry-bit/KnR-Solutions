/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum
number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
When either a tab or a single blank would suffice to reach a tab stop, which should be given
preference? */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define TAB_WIDTH 4

int get_line(char line[], int buffer_limit);

void string_format_to_tabs(const char line[], char line_formatted[], int buffer_limit, int tab_width);

int main()
{
    char line[MAX_LINE_LENGTH];
    char line_formatted[MAX_LINE_LENGTH];

    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        string_format_to_tabs(line, line_formatted, MAX_LINE_LENGTH, TAB_WIDTH);
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

void string_format_to_tabs(const char line[], char line_formatted[], int buffer_limit, int tab_width)
{
    int current_char;
    int pos = 0;
    int formatted_pos = 0;
    int column_char_count = 0;
    int space_count = 0;

    while ((current_char = line[pos]) != '\0' && formatted_pos < buffer_limit - 1)
    {
        ++column_char_count;

        if (current_char == ' ')
        {
            ++space_count;

            while (line[pos + 1] == ' ' && column_char_count != tab_width)
            {
                ++column_char_count;
                ++space_count;
                ++pos;
            }

            if (column_char_count == tab_width && space_count > (tab_width / 2))
            {
                line_formatted[formatted_pos++] = '\t';
                space_count = 0;
            }
            else
            {
                do
                {
                    line_formatted[formatted_pos++] = ' ';
                } while ((--space_count) != 0);
            }
        }
        else
            line_formatted[formatted_pos++] = current_char;

        if (column_char_count == tab_width || current_char == '\t')
            column_char_count = 0;

        ++pos;
    }

    line_formatted[formatted_pos] = '\0';
}