/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input. */

#include <stdio.h>
#include <ctype.h>

#define MAX_BUFF 100

static char buff[MAX_BUFF];
static int buffp = 0;

int getch(void);
void ungetch(int c);
int getint(int *pn);

int main()
{
	int num = 0;

	while (getint(&num))
		printf("Check(getint): %d\n", num);

	return 0;
}

int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch())) {
	}

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(sign == 1 ? '+' : '-');
			ungetch(c);
			return 0;
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int getch(void)
{
	return (buffp > 0) ? buff[--buffp] : getchar();
}

void ungetch(int c)
{
	if (buffp >= MAX_BUFF)
		printf("ungetch: too many characters\n");
	else if (c != EOF)
		buff[buffp++] = c;
}