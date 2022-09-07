/* Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the
string s in place. */

#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main()
{
	char test_array[] = ".*,&";

	printf("Normal: %s\n", test_array);
	reverse(test_array);

	printf("Reverse-1: %s\n", test_array);
	reverse(test_array);

	printf("Reverse-2: %s\n", test_array);

	return 0;
}

void reverse(char s[])
{
	int tmp;
	static int i, end;

	if (end == 0)
		end = strlen(s) - 1;

	if (s[end] == '\0')
		--end;

	if (end > 0 && end - i > 0) {
		tmp = s[i];
		s[i++] = s[end];
		s[end--] = tmp;
		reverse(s);
	} else {
		i = 0;
		end = 0;
	}
}
