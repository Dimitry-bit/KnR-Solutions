/* Exercise 4-5. Add access to library functions like sin, exp, and pow. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "calc.h"

#define MAX_OP 100

static bool skipNLStackPop = false;

void handle_mathf(char s[]);

int main()
{
	double op2;
	char s[MAX_OP];
	int type;

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			stack_push(atof(s));
			break;
		case '+':
			stack_push((stack_pop()) + (stack_pop()));
			break;
		case '*':
			stack_push(stack_pop() * stack_pop());
			break;
		case '-':
			op2 = stack_pop();
			stack_push((stack_pop()) - (op2));
			break;
		case '/':
			op2 = stack_pop();
			stack_push(stack_pop() / op2);
			break;
		case '%':
			op2 = stack_pop();
			stack_push((int) stack_pop() % (int) op2);
			break;
		case IDENTIFIER:
			handle_mathf(s);
			break;
		case '~':
			stack_swap();
			break;
		case '!':
			stack_clear();
			skipNLStackPop = true;
		case '\n':
			skipNLStackPop ? (skipNLStackPop = false) : printf("\t%.8g\n", stack_pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			stack_clear();
			skipNLStackPop = true;
			break;
		}
	}
	return 0;
}

void handle_mathf(char s[])
{
	double op2;

	if (strcmp(s, "SIN") == 0) {
		stack_push(sin(stack_pop()));
	} else if (strcmp(s, "COS") == 0) {
		stack_push(cos(stack_pop()));
	} else if (strcmp(s, "TAN") == 0) {
		stack_push(tan(stack_pop()));
	} else if (strcmp(s, "EXP") == 0) {
		stack_push(exp(stack_pop()));
	} else if (strcmp(s, "POW") == 0) {
		op2 = stack_pop();
		stack_push(pow(stack_pop(), op2));
	} else {
		printf("error: unknown command %s\n", s);
		skipNLStackPop = true;
		stack_clear();
	}
}