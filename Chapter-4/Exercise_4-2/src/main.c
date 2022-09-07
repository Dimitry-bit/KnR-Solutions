/* Exercise 4-2. Extend atof to handle scientific notation of the form 123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent. */

#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define MAX_LINE 1000

double atof_n(char s[]);

int main()
{
	char line[MAX_LINE] = "123.45e0.7";
	printf("Number: %f", atof_n(line));

	return 0;
}

double atof_n(char s[])
{
	double val, power, expo_power;
	int i, sign;

	i = 0;
	while (isspace(s[i]))
		i++;

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;

	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}

	expo_power = 0;
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		expo_power = atof_n(s + i);
	}

	return (sign * val / power) * pow(10, expo_power);
}