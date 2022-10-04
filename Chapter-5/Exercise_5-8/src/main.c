/* Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect. */

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
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (year < 1 || month < 1 || day < 1 || day > daytab[leap][month])
		return 0;

	for (i = 1; i < month; ++i) {
		day += daytab[leap][i];
	}

	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (year < 1 || yearday < 1 || yearday > (leap ? 366 : 365))
		return 0;

	for (i = 1; yearday > daytab[leap][i]; ++i)
		yearday -= daytab[leap][i];

	*pmonth = i;
	*pday = yearday;
	return yearday;
}