#include "calc.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

char buf[BUF_SIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);
void ungets(char s[]);

int getop(char s[])
{
	int i, c, ret;

	while ((s[0] = c = getch()) == ' ' || c == '\t') {
	}

	s[1] = '\0';

	i = 0;
	if (c == '-') {
		s[++i] = c = getch();

		if (!isdigit(c)) {
			ungetch(c);
			return '-';
		}
	} else if (!isalnum(c) && c != '.') {
		return c;
	}

	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch())) {
		}

		ret = NUMBER;
	}

	if (c == '.') {
		while (isdigit(s[++i] = c = getch())) {
		}

		ret = NUMBER;
	}

	if (isalpha(c)) {
		while (isalpha(s[++i] = c = getch())) {
		}

		ret = IDENTIFIER;
	}

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);

	return ret;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUF_SIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char s[])
{
	int len = strlen(s);

	if (BUFSIZ - bufp >= len) {
		for (int i = len - 1; i >= 0; --i)
			ungetch(s[i]);
	} else {
		printf("ungets: too many characters\n");
	}
}

void str_to_upper(char s[])
{
	int i;

	i = 0;
	while (s[i] != '\0') {
		s[i] = toupper(s[i]);
		++i;
	}
}
