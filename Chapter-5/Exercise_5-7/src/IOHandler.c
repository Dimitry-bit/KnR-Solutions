#include <stdio.h>
#include <string.h>
#include "sort.h"

#define ALLOCSIZE 1000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int getline_n(char *s, int lim);

int readlines_alloc(char *lineptr[], int maxlines)
{
	char *p, line[MAX_LEN];
	int len, nlines;

	nlines = 0;
	while ((len = getline_n(line, MAX_LEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

// Needs Cleaning
int readline_noalloc(char lineptr[][MAX_LEN], int maxlines)
{
	char line[MAX_LEN];
	int len, nlines;

	nlines = 0;
	while ((len = getline_n(line, MAX_LEN)) > 0) {
		if (nlines >= maxlines) {
			return -1;
		} else {
			line[len - 1] = '\0';
			strcpy(lineptr[nlines++], line);
		}
	}
	return nlines;

}

int writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
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

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocbuf >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}

}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}