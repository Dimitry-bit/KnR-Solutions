/* Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. Add
the modulus (%) operator and provisions for negative numbers. */

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAX_OP 100

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
		case '\n':
			printf("\t%.8g\n", stack_pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}