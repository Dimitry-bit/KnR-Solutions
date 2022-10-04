#ifndef CALC_H
#define CALC_H

#include <stdbool.h>

#define NUMBER '0'
#define IDENTIFIER 1
#define INVALIDEXP -1

int getop_str(char *s, char *t);
void str_to_upper(char s[]);

bool stack_is_empty(void);
double stack_pop(void);
void stack_push(double f);
double stack_peak(void);
void stack_clear(void);
void stack_swap(void);

#endif //CALC_H