/* Exercise 1-24. Write a program to check a C program for rudimentary syntax errors like
unmatched parentheses, brackets and braces. Don't forget about quotes, both single and
double, escape sequences, and comments. (This program is hard if you do it in full
generality.) */

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define ANSI_COLOR_RED     "\033[31m"
#define ANSI_COLOR_GREEN   "\033[32m"
#define ANSI_COLOR_YELLOW  "\033[93m"
#define ANSI_COLOR_RESET   "\033[0m"

#define COMMENT_OLD_STYLE_START 1
#define COMMENT_OLD_STYLE_END 2
#define COMMENT_NEW_STYLE 3

#define MAX_DEPTH 90

bool is_escape_sequence(char escape_sequence);

bool is_quotation_mark(char syntax);

bool is_syntax_open(char syntax);

bool is_syntax_close(char syntax);

bool is_comment(char current_char, char prev_char, int *out_comment_type);

char reverse_syntax(char syntax);

void log_warning(const char *fmt, ...);

void log_error(const char *fmt, ...);

int main()
{
    char current_char;
    char prev_char;
    char quotation_type;
    char syntax_array[MAX_DEPTH];

    int depth_index = 0;
    int line_char_count = 0;
    int line_count = 1;

    bool is_in_comment = false;
    bool is_escaped = false;
    bool is_string_literal = false;

    bool has_syntax_error = false;
    bool has_unknown_escape_sequence = false;

    while ((current_char = getchar()) != EOF)
    {
        ++line_char_count;

        if (current_char == '\n' || current_char == '\v')
        {
            // Check for missing single/double quotes
            if (is_string_literal)
            {
                log_warning("missing terminating %c character %d:%d\n", quotation_type, line_count, line_char_count);
                is_string_literal = false;
                has_syntax_error = true;
            }

            if (current_char == '\n')
                line_char_count = 0;

            ++line_count;
        }

        // Check for escape character
        if (!is_in_comment && current_char == '\\')
        {
            if (is_string_literal && !is_escaped)
            {
                is_escaped = true;
                continue;
            }
            else if (!is_string_literal)
            {
                log_error("stray ‘\\’ in program %d:%d\n", line_count, line_char_count);
                has_syntax_error = true;
                continue;
            }
        }

        // Check for string literals
        if (!is_in_comment && !is_escaped && is_quotation_mark(current_char))
        {
            if (!is_string_literal)
            {
                quotation_type = current_char;
                is_string_literal = true;
            }
            else if (quotation_type == current_char)
            {
                is_string_literal = false;
            }
        }

        // Check for comments
        int comment_type;
        if (!is_string_literal && is_comment(current_char, prev_char, &comment_type))
        {
            if (comment_type == COMMENT_NEW_STYLE)
            {
                while ((current_char = getchar()) != EOF && current_char != '\n')
                    continue;

                if (current_char == '\n')
                {
                    line_char_count = 0;
                    ++line_count;
                }
            }
            else if (comment_type == COMMENT_OLD_STYLE_START)
                is_in_comment = true;
            else if (comment_type == COMMENT_OLD_STYLE_END)
            {
                if (is_in_comment)
                {
                    is_in_comment = false;
                }
                else
                {
                    log_error("expected statement before ‘/*’ token %d:%d\n", line_count, line_char_count);
                    has_syntax_error = true;
                }
            }
        }

        // Check for rudimentary syntax errors
        if (!is_in_comment && !is_string_literal)
        {
            if (is_syntax_open(current_char))
            {
                syntax_array[depth_index] = current_char;
                ++depth_index;
            }
            else if (is_syntax_close(current_char))
            {
                if (depth_index == 0)
                {
                    log_error("expected statement before ‘%c’ token %d:%d\n", current_char, line_count,
                              line_char_count);
                    has_syntax_error = true;
                }
                else if (syntax_array[depth_index - 1] != reverse_syntax(current_char))
                {
                    log_error("expected ‘%c’ before ‘%c’ token %d:%d\n", reverse_syntax(syntax_array[depth_index - 1]),
                              current_char, line_count, line_char_count);
                    has_syntax_error = true;
                }
                else if (depth_index > 0)
                {
                    --depth_index;
                }
            }
        }
        else if (!is_in_comment && is_string_literal)
        {
            // Check for unknown escape sequences
            if (is_escaped && !is_escape_sequence(current_char))
            {
                log_warning("unknown escape sequence: '\\%c' %d:%d\n", current_char, line_count, line_char_count);
                has_unknown_escape_sequence = true;
            }
        }

        prev_char = current_char;
        is_escaped = false;
    }

    if (is_in_comment)
    {
        log_warning("missing terminating ‘*/’ character %d:%d\n", line_count, line_char_count);
        has_syntax_error = true;
    }

    // Checks if all '[' , '{' , '(' are closed
    while (depth_index != 0)
    {
        log_error("expected ‘%c’ token %d:%d\n", reverse_syntax(syntax_array[depth_index - 1]),
                  line_count, line_char_count);
        ++line_char_count;
        --depth_index;
    }

    printf("\nCheck Results:\n");
    printf("--------------\n");

    if (!has_syntax_error)
        printf("[" ANSI_COLOR_GREEN "PASSED" ANSI_COLOR_RESET "] Rudimentary check.\n");
    else
        printf("[" ANSI_COLOR_RED "FAILED" ANSI_COLOR_RESET "] Rudimentary check.\n");

    if (!has_unknown_escape_sequence)
        printf("[" ANSI_COLOR_GREEN "PASSED" ANSI_COLOR_RESET "] Escape sequence check.\n");
    else
        printf("[" ANSI_COLOR_RED "FAILED" ANSI_COLOR_RESET "] Escape sequence check.\n");

    return 0;
}

bool is_escape_sequence(char escape_sequence)
{
    return escape_sequence == 'a' || escape_sequence == 'b' || escape_sequence == 'f' || escape_sequence == 'n' ||
           escape_sequence == 'r' || escape_sequence == 't' || escape_sequence == 'v' || escape_sequence == '\\' ||
           escape_sequence == '0' || is_quotation_mark(escape_sequence);
}

bool is_syntax_open(char syntax)
{
    return syntax == '[' || syntax == '(' || syntax == '{';
}

bool is_syntax_close(char syntax)
{
    return syntax == ']' || syntax == ')' || syntax == '}';
}

bool is_quotation_mark(char syntax)
{
    return syntax == '"' || syntax == '\'';
}

bool is_comment(char current_char, char prev_char, int *out_comment_type)
{
    *out_comment_type = 0;

    if (current_char == '/' && prev_char == '/')
        *out_comment_type = COMMENT_NEW_STYLE;
    else if (prev_char == '/' && current_char == '*')
        *out_comment_type = COMMENT_OLD_STYLE_START;
    else if (prev_char == '*' && current_char == '/')
        *out_comment_type = COMMENT_OLD_STYLE_END;

    return *out_comment_type;
}

char reverse_syntax(char syntax)
{
    switch (syntax)
    {
        case ']':
            return '[';
        case ')':
            return '(';
        case '}':
            return '{';
        case '[':
            return ']';
        case '(':
            return ')';
        case '{':
            return '}';
        default:
            return syntax;
    }
}

void log_warning(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("[" ANSI_COLOR_YELLOW "WARNING" ANSI_COLOR_RESET "] ");
    vprintf(fmt, args);
    va_end(args);
}

void log_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("[" ANSI_COLOR_RED " ERROR " ANSI_COLOR_RESET "] ");
    vprintf(fmt, args);
    va_end(args);
}