/* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise. */

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main()
{
	char s[] = "Hello, World!";
	char t[] = "World!";

	printf("s=\"%s\"\nt=\"%s\"\n", s, t);
	printf("Check(strend): Pattern%s found", strend(s, t) ? "" : " not");

	return 0;
}

int strend(char *s, char *t)
{
	unsigned long t_len, s_len;

	s_len = strlen(s);
	t_len = strlen(t);

	if (s_len >= t_len) {
		s += s_len - t_len;
		while (*t != '\0' && *s++ == *t++) {
		}
	}

	return (*t == '\0') ? 1 : 0;
}