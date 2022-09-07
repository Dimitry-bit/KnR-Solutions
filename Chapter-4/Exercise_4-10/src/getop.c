#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define MAX_LINE_LENGTH 1000

int getline_n(char s[], int lim);

int getop(char s[])
{
	int i, c, ret;
	static char line[MAX_LINE_LENGTH];
	static int linep;

	if (line[linep] == '\0') {
		if (getline_n(line, MAX_LINE_LENGTH) != 0)
			linep = 0;
		else
			return EOF;
	}

	while ((s[0] = c = line[linep++]) == ' ' || c == '\t') {
	}

	s[1] = '\0';

	i = 0;
	if (c == '-') {
		s[++i] = c = line[linep++];

		if (!isdigit(c)) {
			--linep;
			return '-';
		}
	} else if (!isalnum(c) && c != '.') {
		return c;
	}

	if (isdigit(c)) {
		while (isdigit(s[++i] = c = line[linep++])) {
		}

		ret = NUMBER;
	}

	if (c == '.') {
		while (isdigit(s[++i] = c = line[linep++])) {
		}

		ret = NUMBER;
	}

	if (isalpha(c)) {
		while (isalpha(s[++i] = c = line[linep++])) {
		}

		ret = IDENTIFIER;
	}

	s[i] = '\0';
	if (c != EOF)
		--linep;

	return ret;
}

int getline_n(char s[], int lim)
{
	int i, c;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';
	return i;
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