/* Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>

void strcat_n(char *s, char *t);

int main()
{
	char s[100] = "Hello, ";
	char t[] = "World";

	printf("s=\"%s\"\nt=\"%s\"\n", s, t);
	strcat_n(s, t);
	printf("Check(strcat): s=\"%s\"\n", s);

	return 0;
}

void strcat_n(char *s, char *t)
{
	while (*s != '\0')
		++s;

	while ((*s++ = *t++) != '\0') {
	}
}
