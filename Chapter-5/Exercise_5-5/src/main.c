/* Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B. */

#include <stdio.h>

#define MAX_LINE 100
void strncpy_n(char *s, char *t, long n);
void strncat_n(char *s, char *t, long n);
int strncmp_n(char *s, char *t, long n);

int main()
{
	int result;

	char s1[MAX_LINE] = "Hello, ";
	char t1[MAX_LINE] = "World!";

	char s2[MAX_LINE] = "Hello, ";
	char t2[MAX_LINE] = "World!";

	char s3[MAX_LINE] = "Pattern";
	char t3[MAX_LINE] = "Pattern";

	printf("Check(strncat): ");
	strncat_n(s1, t1, 2);
	printf("%s\n", s1);

	printf("Check(strncpy): ");
	strncpy_n(s2, t2, 2);
	printf("%s\n", s2);

	printf("Check(strncmp): ");
	if ((result = strncmp_n(s3, t3, 2)) < 0)
		printf("STR1 < STR2\n");
	else if (result > 0)
		printf("STR2 < STR1\n");
	else
		printf("STR1 == STR2\n");

	return 0;
}

void strncat_n(char *s, char *t, long n)
{
	while (*s != '\0')
		++s;

	for (; n > 0 && *t; --n) {
		*s++ = *t++;
	}

	*s = '\0';
}

void strncpy_n(char *s, char *t, long n)
{
	for (; n > 0 && *t; --n) {
		*s++ = *t++;
	}

	*s = '\0';
}

int strncmp_n(char *s, char *t, long n)
{
	while (n > 0 && *s && *s == *t) {
		++s;
		++t;
		--n;
	}

	if (n == 0)
		return 0;
	else
		return *s - *t;
}