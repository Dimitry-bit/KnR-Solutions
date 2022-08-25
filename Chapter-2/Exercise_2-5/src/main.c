#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
    char s1[1000] = "aNbifcgeh jckoldmen!";
    char s2[1000] = "abfghjklmn";
    int n = any(s1, s2);
    printf("[%d] --> %c \n", n, s1[n]);
    return 0;
}

int any(char s1[], char s2[])
{
    for (int i = 0; s1[i] != '\0'; ++i)
    {
        for (int j = 0; s2[j]; ++j)
        {
            if (s1[i] == s2[j])
                return i;
        }
    }

    return -1;
}