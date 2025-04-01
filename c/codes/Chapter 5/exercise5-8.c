#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        printf("Invalid date\n");
        return -1;
    }

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (day > daytab[leap][month]) {
        printf("Invalid day for the given month\n");
        return -1;
    }

    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (year < 1 || yearday < 1 || (leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0), yearday > (leap ? 366 : 365))) {
        printf("Invalid year or day of year\n");
        *pmonth = *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }

    *pmonth = i;
    *pday = yearday;
}

int main() {
    int month, day;
    
    printf("Day of year: %d\n", day_of_year(2024, 2, 29));  // Valid leap year
    printf("Day of year: %d\n", day_of_year(2023, 2, 29));  // Invalid non-leap year
    
    month_day(2024, 60, &month, &day);  // Valid day of year
    printf("Month: %d, Day: %d\n", month, day);

    month_day(2024, 400, &month, &day);  // Invalid day of year
    printf("Month: %d, Day: %d\n", month, day);

    return 0;
}
