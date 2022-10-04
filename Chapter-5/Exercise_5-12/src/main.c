/* Exercise 5-12. Extend entab and detab to accept the shorthand "entab -m +n" to mean tab stops every n columns,
starting at column m. Choose convenient (for the user) default behavior. */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000
#define DEFAULT_TAB_WIDTH 8

static int tab_width = DEFAULT_TAB_WIDTH;

int get_line(char *s, int lim);
void entab(const char *s, char *t, int lim);
void detab(const char *s, char *t, int lim);

int main(int argc, char *argv[])
{
	char s[MAX_LINE_LENGTH], t[MAX_LINE_LENGTH], *s_end;
	int c, is_detab;
	void (*func)(const char *, char *, int);

	is_detab = 0;
	func = entab;
	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
			case 'w':
				if (--argc > 0 && (c = strtol(*++argv, &s_end, 10))) {
					tab_width = c;
					argv[0] = s_end - 1;
				}
				break;
			case 'd':
				func = detab;
				is_detab = 1;
				break;
			default:
				printf("entab: illegal option %c\n", c);
				argc = 0;
				is_detab = 0;
				func = entab;
				break;
			}
		}
	}

	printf("%s:\n", is_detab ? "Detab" : "Entab");
	while (get_line(s, MAX_LINE_LENGTH) > 0) {
		func(s, t, MAX_LINE_LENGTH);
		printf("%s", t);
	}
	return 0;
}

int get_line(char *s, int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}

void entab(const char *s, char *t, int lim)
{
	int c, c_count, ws_count;

	c_count = ws_count = 0;
	while (--lim > 0 && (c = *s++) != '\0') {
		++c_count;

		if (c == ' ') {
			++ws_count;

			for (; *s == ' ' && c_count != tab_width; ++s) {
				++c_count;
				++ws_count;
			}

			if (c_count == tab_width && ws_count > (tab_width / 2)) {
				*t++ = '\t';
				ws_count = 0;
			} else {
				do {
					*t++ = ' ';
				} while ((--ws_count) != 0);
			}
		} else {
			*t++ = c;
		}

		if (c_count == tab_width || c == '\t')
			c_count = 0;
	}

	*t = '\0';
}

void detab(const char *s, char *t, int lim)
{
	int c, c_count;

	c_count = 0;
	while (--lim > 0 && (c = *s++) != '\0') {
		if (c == '\t') {
			while (--lim > 0 && c_count != tab_width) {
				*t++ = ' ';
				++c_count;
			}
		} else {
			*t++ = c;
			++c_count;
		}

		if (c_count == tab_width)
			c_count = 0;
	}

	*t = '\0';
}
