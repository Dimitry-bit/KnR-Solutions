#ifndef SORT_H
#define SORT_H

#define MAX_LEN 1000
#define MAX_LINES 5000

int readlines_alloc(char *lineptr[], int maxlines);
int readline_noalloc(char lineptr[][MAX_LEN], int maxlines);
int writelines(char *lineptr[], int nlines);

char *alloc(int n);
void afree(char *p);

#endif //SORT_H
