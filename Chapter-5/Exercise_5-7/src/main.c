/* Exercise 5-7. Rewrite readlines_alloc to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program? */

#include <stdio.h>
#include <string.h>
#include "sort.h"

#define IS_ALLOC 1

void qsort(char *lineptr[], int left, int right);

int main()
{
	int nlines;
	char line[MAX_LEN];

#ifdef IS_ALLOC
	char *lineptr[MAX_LINES];

	if ((nlines = readlines_alloc(lineptr, MAX_LINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
#else
	char lineptr[MAX_LINES][MAX_LEN];
	if ((nlines = readline_noalloc(lineptr, MAX_LINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
#endif
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right) /* do nothing if array contains */
		return;

	/* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}