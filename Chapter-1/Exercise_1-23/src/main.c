/* Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to
handle quoted strings and character constants properly. C comments don't nest. */

#include <stdio.h>
#include <stdbool.h>

#define COMMENT_OLD_STYLE_START 1
#define COMMENT_OLD_STYLE_END 2
#define COMMENT_NEW_STYLE 3

bool is_comment(char current_char, char prev_char, int *out_comment_type);

bool is_quotation_mark(char syntax);

int main()
{
    int comment_type;

    char quotation_type;
    char current_char;
    char prev_char = -1;

    bool is_string_literal;
    bool is_in_comment;
    bool is_escaped;

    while ((current_char = getchar()) != EOF)
    {
        if (is_in_comment)
        {
            if (comment_type == COMMENT_NEW_STYLE)
            {
                while ((current_char = getchar()) != EOF && current_char != '\n')
                    continue;
            }
            else if (comment_type == COMMENT_OLD_STYLE_START)
            {
                while (comment_type != COMMENT_OLD_STYLE_END)
                {
                    is_comment(current_char, prev_char, &comment_type);
                    prev_char = current_char;
                    current_char = getchar();
                }
            }

            if (comment_type == COMMENT_OLD_STYLE_END || comment_type == COMMENT_NEW_STYLE)
            {
                prev_char = -1;
                is_in_comment = false;
                continue;
            }
        }

        if (!is_escaped && is_quotation_mark(current_char))
        {
            if (!is_string_literal)
            {
                is_string_literal = true;
                quotation_type = current_char;
            }
            else if (quotation_type == current_char)
            {
                is_string_literal = false;
            }
        }

        if (!is_string_literal && is_comment(current_char, prev_char, &comment_type))
        {
            if (comment_type == COMMENT_NEW_STYLE || comment_type == COMMENT_OLD_STYLE_START)
                is_in_comment = true;
        }
        else if (prev_char != -1)
        {
            putchar(prev_char);
        }

        is_escaped = current_char == '\\' && is_string_literal ? !is_escaped : false;
        prev_char = current_char;
    }

    return 0;
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

bool is_quotation_mark(char syntax)
{
    return syntax == '"' || syntax == '\'';
}