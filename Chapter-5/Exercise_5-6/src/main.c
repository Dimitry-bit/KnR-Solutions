/* Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4). */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100
#define NUMBER '0'
#define IDENTIFIER 1
#define MAX_LEN 100

char buf[BUF_SIZE];
char *bufp = buf;

int getline_n(char *s, int lim);
int strindex_n(char *s, char *t);
int atoi_n(char *s);
void itoa(int n, char *s);
void reverse(char *s);
int getop(char *s);
int getch(void);
void ungetch(int c);

int main()
{
	char val[MAX_LEN];
	static char pattern[] = "Potato";
	static char pattern_test[][MAX_LEN] = {
	    "PotatoMan", "BigPotato", "Mediumpotato", "smallpotato"
	};
	int num, strindex_pos, getop_type, len;

	num = atoi_n("-42069");
	printf("Check(atoi): %d\n", num);
	itoa(num, val);
	printf("Check(itoa): %s\n", val);

	putchar('\n');

	printf("STRs: ");
	for (int i = 0; i < 4; ++i)
		printf("\"%s\"%s", pattern_test[i], i != 3 ? ", " : "");
	printf("\nPattern: \"%s\"\n", pattern);
	for (int i = 0; i < 4; ++i) {
		if ((strindex_pos = strindex_n(*(pattern_test + i), pattern)) >= 0)
			printf("Check(strindex): \"%s\":%d\n", *(pattern_test + i), strindex_pos);
	}

	putchar('\n');

	printf("Check(getline):\n");
	printf("-> ");
	len = getline_n(val, MAX_LEN);
	printf("Check(getline):\"%s\":%d\n", val, len);

	putchar('\n');

	printf("Check(getop):\n");
	printf("-> ");
	while ((getop_type = getop(val)) != EOF) {
		switch (getop_type) {
		case NUMBER:
			printf("Check(getop): %d\n", atoi_n(val));
			break;
		case '\n':
			printf("-> ");
			break;
		case IDENTIFIER:
		default:
			printf("Check(getop): %s\n", val);
			break;
		}
	}

	return 0;
}

int getline_n(char *s, int lim)
{
	char *s_start;
	int c;

	s_start = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s = '\0';
	return s - s_start;
}

int strindex_n(char *s, char *t)
{
	char *s_start, *s2, *t2;
	int pos = -1;

	s_start = s;
	for (; *s; ++s) {
		for (s2 = s, t2 = t; *t2 && *t2 == *s2; ++s2, ++t2) {
		}

		if (t2 > t && *t)
			pos = s - s_start;
	}

	return (pos < 0) ? -1 : pos;
}

int atoi_n(char *s)
{
	int val, sign;

	while (isspace(*s))
		*s++;

	sign = (*s == '-') ? -1 : 1;
	if (*s == '-' || *s == '+')
		*s++;

	val = 0;
	while (isdigit(*s))
		val = 10 * val + (*s++ - '0');

	return sign * val;
}

void itoa(int n, char *s)
{
	char *str_start;
	int sign;

	sign = n;
	str_start = s;

	do {
		*s++ = abs(n % 10) + '0';
	} while (n /= 10);

	if (sign < 0)
		*s++ = '-';

	*s = '\0';
	reverse(str_start);
}

void reverse(char *s)
{
	char *s_end;
	int c;

	for (s_end = s + strlen(s) - 1; s < s_end; ++s, --s_end) {
		c = *s;
		*s = *s_end;
		*s_end = c;
	}
}

int getop(char *s)
{
	int c, ret;

	while ((*s = c = getch()) == ' ' || c == '\t') {
	}

	*(s + 1) = '\0';

	if (c == '-') {
		*++s = c = getch();

		if (!isdigit(c)) {
			ungetch(c);
			return '-';
		}
	} else if (!isalnum(c) && c != '.') {
		return c;
	}

	if (isdigit(c)) {
		while (isdigit(*++s = c = getch())) {
		}

		ret = NUMBER;
	}

	if (c == '.') {
		while (isdigit(*++s = c = getch())) {
		}

		ret = NUMBER;
	}

	if (isalpha(c)) {
		while (isalpha(*++s = c = getch())) {
		}

		ret = IDENTIFIER;
	}

	*s = '\0';
	if (c != EOF)
		ungetch(c);

	return ret;
}

int getch(void)
{
	return (bufp > buf) ? *--bufp : getchar();
}

void ungetch(int c)
{
	if (bufp >= buf + BUF_SIZE)
		printf("ungetch: too many characters\n");
	else
		*bufp++ = c;
}
