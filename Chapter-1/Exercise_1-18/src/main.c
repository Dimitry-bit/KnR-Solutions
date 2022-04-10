/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input,
and to delete entirely blank lines. */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int get_line(char line[], int buffer_limit);

void string_trim_right(char line[]);

int string_trim_left(const char line[]);

int string_trim(char line[]);

int string_length(const char line[]);

int is_space(char character);

int string_is_blank(const char line[]);

int main()
{
    char line[MAX_LINE_LENGTH];

    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        if (string_is_blank(line)) continue;

        int string_start_offset = string_trim(line);
        printf("%s\n", line + string_start_offset);
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

int string_length(const char line[])
{
    int i;

    i = 0;
    while (line[i] != '\0')
        ++i;

    return i;
}

int is_space(char character)
{
    int is_space = 0;

    if (character == ' ' || character == '\t' || character == '\n' || character == '\v' ||
        character == '\f' || character == '\r')
    {
        is_space = 1;
    }

    return is_space;
}

void string_trim_right(char line[])
{
    int i;
    int str_length;

    if ((str_length = string_length(line)) <= 0) return;

    i = str_length - 1;
    while (i > 0 && is_space(line[i]))
        --i;

    line[i + 1] = '\0';
}

int string_trim_left(const char line[])
{
    int i;
    int c;

    i = 0;
    while ((c = line[i]) != '\0' && is_space(c))
        ++i;

    return i;
}

int string_trim(char line[])
{
    string_trim_right(line);
    return string_trim_left(line);
}

int string_is_blank(const char line[])
{
    int is_blank = 0;
    int str_length;

    str_length = string_length(line);
    if (str_length == string_trim_left(line))
        is_blank = 1;

    return is_blank;
}