/* Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to
write a program that reverses its input a line at a time. */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int get_line(char line[], int buffer_limit);

void string_trim_right(char line[]);

void string_reverse(char line[]);

int string_length(const char line[]);

int is_space(char character);

int main()
{
    char line[MAX_LINE_LENGTH];

    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        string_trim_right(line);
        string_reverse(line);
        printf("%s\n", line);
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
    while (i >= 0 && is_space(line[i]))
        --i;

    line[i + 1] = '\0';
}

void string_reverse(char line[])
{
    int end;
    int start;
    int str_length;
    int tmp_char;
    int in_leading_space = 1;

    if ((str_length = string_length(line)) <= 0) return;

    end = str_length - 1;
    start = 0;

    while (line[start] != '\0' && start < end)
    {
        if (!in_leading_space || !is_space(line[start]))
        {
            in_leading_space = 0;

            tmp_char = line[start];
            line[start] = line[end];
            line[end] = tmp_char;

            --end;
        }

        ++start;
    }
}