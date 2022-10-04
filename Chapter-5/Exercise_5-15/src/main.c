/* Exercise 5-15. Add the option -f to fold upper and lower case together, so that case
distinctions are not made during sorting; for example, a and A compare equal. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PROGRAM_NAME "qsort"
#define MAX_LINES 5000
#define MAX_LEN 1000
#define ERR_USAGE -1

static char *linesptr[MAX_LINES];

enum FLAGS {
  numeric = 1 << 0,
  reverse = 1 << 1,
  fold = 1 << 2,
};

unsigned int opts = 0;

void usage(void);
void parse_args(int *argc, char *argv[]);

int getline_n(char *s, int lim);
int readlines(char *lines[], int maxlines);
void writelines(char *lines[], int nlines);
void str_reverse(char *lines[], int nlines);

void qsort_n(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int strcmp_f(char *s1, char *s2);

int main(int argc, char *argv[])
{
	int nlines;
	int (*cmp)(void *, void *);

	parse_args(&argc, argv);
	if (argc == -2) {
		return 0;
	} else if (argc != 0) {
		usage();
		opts = 0;
		return ERR_USAGE;
	}

	if ((nlines = readlines(linesptr, MAX_LINES)) >= 0) {
		cmp = (opts & numeric) ? numcmp : (opts & fold) ? strcmp_f : strcmp;
		qsort_n((void **) linesptr, 0, nlines - 1, cmp);
		if (opts & reverse)
			str_reverse(linesptr, nlines);
		writelines(linesptr, nlines);
	}

	return 0;
}

void usage(void)
{
	printf("Usage: " PROGRAM_NAME " [OPTION]...\n"
	       "  -n		compare according to string numerical value;\n"
	       "  -r		reverse the result of comparison;\n"
	       "  -h 		print usage;\n");
}

void parse_args(int *argc, char *argv[])
{
	while (--*argc > 0 && ++argv) {
		if (strcmp(*argv, "-h") == 0 || strcmp(*argv, "--help") == 0) {
			opts = 0;
			*argc = -2;
			usage();
			return;
		} else if (strcmp(*argv, "-n") == 0 || strcmp(*argv, "--numeric") == 0) {
			opts |= numeric;
		} else if (strcmp(*argv, "-r") == 0 || strcmp(*argv, "--reverse") == 0) {
			opts |= reverse;
		} else if (strcmp(*argv, "-f") == 0 || strcmp(*argv, "--fold") == 0) {
			opts |= fold;
		} else {
			printf(PROGRAM_NAME ": illegal option '%s'\n", *argv);
			*argc = -1;
			return;
		}
	}
}

int getline_n(char *s, int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';
	return i;
}

int readlines(char *lines[], int maxlines)
{
	int len, nlines;
	char *p, line[MAX_LEN];

	nlines = 0;
	while ((len = getline_n(line, MAX_LEN)) > 0) {
		if (nlines >= maxlines || (p = malloc(sizeof(char) * len)) == NULL) {
			return -1;
		} else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lines[nlines++] = p;
		}
	}

	return nlines;
}

void writelines(char *lines[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lines[i]);
}

void qsort_n(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	qsort_n(v, left, last - 1, comp);
	qsort_n(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
	void *tmp;

	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = strtof(s1, NULL);
	v2 = strtof(s2, NULL);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int strcmp_f(char *s1, char *s2)
{
	for (; toupper(*s1) == toupper(*s2); ++s1, ++s2) {
	}
	return toupper(*s1) - toupper(*s2);
}

void str_reverse(char *lines[], int nlines)
{
	char *s;
	int i, j;

	for (i = 0, j = nlines - 1; i < j; i++, j--) {
		s = lines[i];
		lines[i] = lines[j];
		lines[j] = s;
	}
}