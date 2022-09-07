#include <stdio.h>
#include <ctype.h>
#include "calc.h"

char buf = '\0';

int getch(void);
void ungetch(int c);

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
	char c;

	if (buf != '\0') {
		c = buf;
		buf = '\0';
		return c;
	}

	return getchar();
}

void ungetch(int c)
{
	buf = c;
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