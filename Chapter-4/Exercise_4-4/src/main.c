/* Exercise 4-4. Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack. */

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