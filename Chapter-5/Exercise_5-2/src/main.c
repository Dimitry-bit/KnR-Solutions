/* Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does
getfloat return as its function value? */

#include <stdio.h>
#include <ctype.h>

#define MAX_BUFF 100

static char buff[MAX_BUFF];
static int buffp = 0;

int getch(void);
void ungetch(int c);
int getfloat(float *pn);

int main()
{
	float num = 0;

	while (getfloat(&num))
		printf("Check(getfloat): %g\n", num);

	return 0;
}

int getfloat(float *pn)
{
	int c, sign, pow;

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

	pow = 1;
	if (c == '.') {
		while (isdigit(c = getch())) {
			*pn = 10 * *pn + (c - '0');
			pow *= 10;
		}
	}

	*pn = *pn * sign / pow;
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