#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_LINE_LENGTH 1000

void itoa(int n, char s[]);

int main()
{
	char ans_array[MAX_LINE_LENGTH];
	int int_test1 = -420;

	itoa(int_test1, ans_array);
	printf("number: %d\nnumber_s: %s\n", int_test1, ans_array);

	int_test1 = INT32_MIN;
	itoa(int_test1, ans_array);
	printf("number: %d\nnumber_s: %s\n", int_test1, ans_array);

	return 0;
}

void itoa(int n, char s[])
{
	static int i, depth;

	++depth;
	if (n < 0 && i == 0)
		s[i++] = '-';

	if (n / 10)
		itoa(n / 10, s);

	s[i++] = abs(n % 10) + '0';
	--depth;

	if (depth == 0) {
		s[i] = '\0';
		i = 0;
	}
}