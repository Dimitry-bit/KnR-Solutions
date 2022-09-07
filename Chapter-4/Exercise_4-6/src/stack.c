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

void stack_clear(void)
{
	sp = 0;
}

double stack_peak(void)
{
	return sp > 0 ? val[sp - 1] : 0.0;
}

void stack_swap(void)
{
	double tmp;

	if (sp > 1) {
		val[sp - 1] = tmp;
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = tmp;
	} else {
		printf("error: can't swap, only one item in stack\n");
	}
}

bool stack_is_empty(void)
{
	return sp == 0;
}