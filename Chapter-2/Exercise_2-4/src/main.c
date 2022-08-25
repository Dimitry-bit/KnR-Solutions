/* Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2. */
#include <stdio.h>

#define ASCII_CHAR_SET 128

void squeeze(char s1[], const char s2[]);

int main()
{
    char s1[1000] = "aNbifcgeh jckoldmen!";
    char s2[1000] = "abfghjklmn";
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}

void squeeze(char s1[], const char s2[])
{
    int j = 0;
    char s2_chars[ASCII_CHAR_SET];

    for (int i = 0; i < ASCII_CHAR_SET - 1; ++i)
        s2_chars[i] = 0;

    for (int i = 0; s2[i] != '\0'; ++i)
        ++s2_chars[s2[i]];

    for (int i = 0; s1[i] != '\0'; ++i)
    {
        if (s2_chars[s1[i]] == 0)
            s1[j++] = s1[i];
    }

    s1[j] = '\0';
}