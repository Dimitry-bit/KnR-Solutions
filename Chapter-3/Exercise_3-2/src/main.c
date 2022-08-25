/* Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write
a function for the other direction as well, converting escape sequences into the real characters. */

#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000

char is_escape_char(char c);

char char_to_escape(char c);

void escape(char s[], char t[]);

void escape_rev(char s[], char t[]);

int main()
{
    char t[MAX_LINE_LENGTH] = "Hello, World!\n\"Hello World!\n\"";
    char s[MAX_LINE_LENGTH];

    escape(s, t);
    printf("%s\n", s);

    escape_rev(t, s);
    printf("%s\n", t);

    return 0;
}

char is_escape_char(char c)
{
    switch (c)
    {
        case '\n':
            return 'n';
        case '\t':
            return 't';
        case '\b':
            return 'b';
        case '\v':
            return 'v';
        case '\f':
            return 'f';
        case '\r':
            return 'r';
        case '\a':
            return 'a';
        case '\\':
            return '\\';
        default:
            return '\0';
    }
}

char char_to_escape(char c)
{
    switch (c)
    {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case 'b':
            return '\b';
        case 'v':
            return '\v';
        case 'f':
            return '\f';
        case 'r':
            return '\r';
        case 'a':
            return '\a';
        case '\\':
            return '\\';
        default:
            return '\0';
    }
}

void escape(char s[], char t[])
{
    int j;
    char c;

    for (int i = j = 0; t[i] != '\0'; ++i, ++j)
    {
        if ((c = is_escape_char(t[i])) != '\0')
        {
            s[j++] = '\\';
            s[j] = c;
        }
        else
        {
            s[j] = t[i];
        }
    }
    s[j] = '\0';
}

void escape_rev(char s[], char t[])
{
    int j;
    char c;
    char string_marker;
    bool is_escape = false;
    bool is_string_literal = false;

    for (int i = j = 0; t[i] != '\0'; ++i, j++)
    {
        if (t[i] == '\\' && !is_string_literal)
        {
            is_escape = true;
            continue;
        }

        if (is_escape && !is_string_literal)
        {
            is_escape = false;

            if ((c = char_to_escape(t[i])) != '\0')
                s[j] = c;

            ++i;        // Skip escaped character
        }

        if (!is_escape && (t[i] == '\'' || t[i] == '"'))
        {
            if (!is_string_literal)
            {
                is_string_literal = true;
                string_marker = t[i];
            }
            else if (string_marker == t[i])
            {
                is_string_literal = false;
            }
        }

        s[j] = t[i];
    }

    s[j] = '\0';
}