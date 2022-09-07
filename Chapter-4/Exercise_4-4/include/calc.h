#ifndef CALC_H
#define CALC_H

#define NUMBER '0'

int getop(char s[]);

double stack_pop(void);
void stack_push(double f);
double stack_print(void);
void stack_clear(void);
void stack_swap(void);

#endif //CALC_H
