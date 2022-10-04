#include "calc.h"
#include <ctype.h>

int getop_str(char *s, char *t)
{
	int c, ret;

	while ((*s = c = *t++) == ' ' || c == '\t') {
	}

	if (c == '-' && !isdigit(*++s = c = *t++))
		ret = '-';
	else if (!isalnum(c) && c != '.')
		ret = (*++s = c = *t++) == '\0' ? *(s - 1) : INVALIDEXP;

	if (ret != INVALIDEXP) {
		if (isdigit(c)) {
			while (isdigit(*++s = c = *t++)) {
			}

			ret = NUMBER;
		}

		if (c == '.') {
			while (isdigit(*++s = c = *t++)) {
			}

			ret = NUMBER;
		}

		if (isalpha(c)) {
			while (isalpha(*++s = c = *t++)) {
			}

			ret = IDENTIFIER;
		}
	}

	*++s = '\0';
	if (c != '\0')
		ret = INVALIDEXP;

	return ret;
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
