/* Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t.
(Block structure will help.) */

#include <stdio.h>

#define SWAP(t, x, y) { t tmp; tmp = x; x = y; y = tmp;}

int main()
{
	char *str_1 = "potato";
	char *str_2 = "world";
	int int_1 = 420;
	int int_2 = 69;

	printf("int_1 = %d, int_2 = %d\n", int_1, int_2);
	SWAP(int, int_1, int_2);
	printf("int_1 = %d, int_2 = %d\n", int_1, int_2);

	printf("str_1 = %s, str_2 = %s\n", str_1, str_2);
	SWAP(char *, str_1, str_2)
	printf("str_1 = %s, str_2 = %s\n", str_1, str_2);

	return 0;
}
