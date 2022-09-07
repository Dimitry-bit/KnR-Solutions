#include <stdio.h>
#include "calc.h"

#define MAX_VAL 100

int sp = 0;
double val[MAX_VAL];

void stack_push(double f)
{
	if (sp < MAX_VAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double stack_pop(void)
{
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}