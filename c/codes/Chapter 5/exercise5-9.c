#include <stdio.h>

static int daytab[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int *p = daytab[leap];

    if (month < 1 || month > 12 || day < 1 || day > *(p + month - 1)) {
        printf("Invalid date\n");
        return -1;
    }

    int total_days = 0;
    for (int i = 0; i < month - 1; i++) {
        total_days += *(p + i);
    }
    return total_days + day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int *p = daytab[leap];

    if (yearday < 1 || yearday > (leap ? 366 : 365)) {
        printf("Invalid yearday\n");
        *pmonth = *pday = -1;
        return;
    }

    for (*pmonth = 1; yearday > *p; (*pmonth)++) {
        yearday -= *p++;
    }
    *pday = yearday;
}

int main() {
    int month, day;
    printf("Day of year: %d\n", day_of_year(2024, 3, 14));
    month_day(2024, 73, &month, &day);
    printf("Month: %d, Day: %d\n", month, day);

    return 0;
}
