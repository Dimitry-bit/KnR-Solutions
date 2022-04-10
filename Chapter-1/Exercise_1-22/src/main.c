/* Exercise 1-22. Write a program to ``fold'' long input lines into two or more, shorter lines after
the last non-blank character that occurs before the n-th column of input. Make sure your
program does something intelligent with very long lines, and if there are no blanks or tabs
before the specified column. */

#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define FOLD_THRESHOLD 100
#define MAX_CHAR_BACKTRACK 35

int get_line(char line[], int buffer_limit);

int is_space(char character);

int string_length(const char line[]);

void string_trim_right(char line[]);

int string_trim_left(const char line[]);

void string_trim_extra_whitespace(char line[]);

int fold_line(const char line[], int fold_threshold, int max_char_backtrack);

void print_folded(const char line[], int fold_threshold, int max_char_backtrack);

int main()
{
    char line[MAX_LINE_LENGTH];
    char *formatted_line;
    int line_length;
    int fold_threshold = FOLD_THRESHOLD;
    int max_char_backtrack = MAX_CHAR_BACKTRACK;

    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        // Remove extra spaces
        formatted_line = line + string_trim_left(line);
        string_trim_right(formatted_line);
        string_trim_extra_whitespace(formatted_line);

        line_length = string_length(formatted_line);

        if (line_length <= fold_threshold)
            printf("%s\n", formatted_line);
        else
            print_folded(formatted_line, fold_threshold, max_char_backtrack);
    }

    return 0;
}

int get_line(char line[], int buffer_limit)
{
    char current_char;
    int i;

    for (i = 0; i < buffer_limit - 1 && (current_char = getchar()) != EOF && current_char != '\n'; ++i)
        line[i] = current_char;

    if (current_char == '\n')
    {
        line[i] = current_char;
        ++i;
    }

    line[i] = '\0';
    return i;
}

int is_space(char character)
{
    return (character == ' ' || character == '\t' || character == '\n' || character == '\v' ||
            character == '\f' || character == '\r');
}

int string_length(const char line[])
{
    int i;

    i = 0;
    while (line[i] != '\0')
        ++i;

    return i;
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
    char current_char;

    i = 0;
    while ((current_char = line[i]) != '\0' && is_space(current_char))
        ++i;

    return i;
}

void string_trim_extra_whitespace(char line[])
{
    int pos = 0;
    int formatted_pos = 0;
    char current_char;
    char previous_char = 0;

    while ((current_char = line[pos]) != '\0')
    {
        if (!(is_space(current_char) && is_space(previous_char)))
        {
            if (formatted_pos == pos)
                ++formatted_pos;
            else
                line[formatted_pos++] = line[pos];
        }

        previous_char = current_char;
        ++pos;
    }

    line[formatted_pos] = '\0';
}

int fold_line(const char line[], int fold_threshold, int max_char_backtrack)
{
    int pos = 0;
    char current_char;
    int current_word_length = 0;
    int exceeded_threshold = 0;

    while ((current_char = line[pos]) != '\0')
    {
        if (pos >= fold_threshold)
        {
            exceeded_threshold = 1;
            break;
        }

        if (is_space(current_char))
            current_word_length = 0;
        else
            ++current_word_length;

        ++pos;
    }

    if (exceeded_threshold && (current_word_length <= max_char_backtrack))
        pos -= current_word_length;

    return pos;
}

void print_folded(const char line[], int fold_threshold, int max_char_backtrack)
{
    int fold_char_width;

    while (*line != '\0')
    {
        fold_char_width = fold_line(line, fold_threshold, max_char_backtrack);
        const char *fold_end_ptr = line + fold_char_width;

        while (line != fold_end_ptr)
            printf("%c", *line++);

        printf("\n");
    }
}
