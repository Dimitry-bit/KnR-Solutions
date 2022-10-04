/* Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of
indexing.*/
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
	int year, month, day, yearday;

	year = 2004;
	month = 1;
	day = 8;

	if ((yearday = day_of_year(year, month, day)))
		printf("%d/%d/%d <---> %d:%d\n", day, month, year, year, yearday);
	else
		printf("Incorrect input\n");

	if (month_day(year, yearday, &month, &day))
		printf("%d:%d <---> %d/%d/%d\n", year, yearday, day, month, year);
	else
		printf("Incorrect input\n");

	return 0;
}

int day_of_year(int year, int month, int day)
{
	int leap;
	char *p;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (year < 1 || month < 1 || day < 1 || day > (*(daytab + leap))[month])
		return 0;

	p = &(*(daytab + leap))[1];
	while (--month)
		day += *p++;

	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	char *p, *p_start;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (year < 1 || yearday < 1 || yearday > (leap ? 366 : 365))
		return 0;

	p_start = &(*(daytab + leap))[1];
	for (p = p_start; yearday > *p; ++p)
		yearday -= *p;

	*pmonth = (int) ((p - p_start) + 1);
	*pday = yearday;
	return yearday;
}
