/* Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide
what their properties ought to be if an EOF is pushed back, then implement your design. */

#include <stdio.h>

#define BUF_SIZE 100

char buf[BUF_SIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);

int main()
{
	char c;

	/* Prematurely send EOF. */
	ungetch(EOF);

	while ((c = getch()) != EOF)
		putchar(c);

	return 0;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUF_SIZE)
		printf("ungetch: too many characters\n");
	else if (c != EOF)
		buf[bufp++] = c;
}