/* Exercise 4-1. Write the function str_index(s,t) which returns the position of the rightmost
occurrence of t in s, or -1 if there is none. */

#include <stdio.h>

#define MAX_LINE 100

char pattern[] = "ould";

int get_line(char s[], int limit);
int str_index(char s[], char t[]);

int main()
{
	char line[MAX_LINE];
	int found;
	int pattern_index;

	found = 0;
	while (get_line(line, MAX_LINE) > 0) {
		if ((pattern_index = str_index(line, pattern)) >= 0) {
			printf("%sindex:%d\n", line, pattern_index);
			found++;
		}
	}
	return found;
}

int get_line(char s[], int limit)
{
	int c, i;

	i = 0;
	while (--limit > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

int str_index(char s[], char t[])
{
	int i, j, k;
	int pos = -1;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
		}

		if (k > 0 && t[k] == '\0')
			pos = i;
	}

	return (pos >= 0) ? pos : -1;
}
