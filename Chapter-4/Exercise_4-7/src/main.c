/* Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch? */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "calc.h"

#define MAX_OP 100
#define VAR_STACK_MAX 26

static bool skipNLStackPop = false;
static double var_stack[VAR_STACK_MAX];

void handle_mathf(char s[]);
void calc_set_var(char c);
void var_stack_print(void);

int main()
{
	double op2, ans;
	char s[MAX_OP];
	char current_var;
	int type;

	ans = 0;
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
			str_to_upper(s);
			if (strlen(s) == 1) {
				current_var = s[0];
				stack_push(var_stack[current_var - 'A']);
			} else if (strcmp(s, "ANS") == 0) {
				stack_push(ans);
			} else {
				handle_mathf(s);
			}
			break;
		case '=':
			calc_set_var(current_var);
			break;
		case '?':
			var_stack_print();
			break;
		case '~':
			stack_swap();
			break;
		case '!':
			stack_clear();
			printf("stack cleared\n");
			skipNLStackPop = true;
			break;
		case '\n':
			if (!skipNLStackPop) {
				if (!stack_is_empty())
					ans = stack_pop();
				printf("ANS: %.8g\n", ans);
			}
			skipNLStackPop = false;
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

void calc_set_var(char c)
{
	if (c >= 'A' && c <= 'Z') {
		if (!stack_is_empty())
			stack_pop();        // clear variable value from stack
		var_stack[c - 'A'] = stack_peak();
	} else {
		printf("error: invalid variable\n");
	}
}

void var_stack_print(void)
{
	int line_var_count = 0;
	for (int i = 0; i <= VAR_STACK_MAX - 1; ++i) {
		if (var_stack[i] != 0) {
			printf("%c: %.8g    ", 'A' + i, var_stack[i]);
			line_var_count++;

			if (line_var_count != 0 && line_var_count % 5 == 0) {
				printf("\n");
				line_var_count = 0;
			}
		}
	}

	if (line_var_count % 5 != 0)
		printf("\n");
}
