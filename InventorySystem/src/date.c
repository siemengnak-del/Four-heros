#include <stdio.h>
#include <time.h>
#include "../include/date.h"




date timenow() {
    time_t current_time = time(NULL);

    struct tm t = *localtime(&current_time);

    date today;

    today.days = t.tm_mday;
    today.months = t.tm_mon + 1;
    today.years = t.tm_year + 1900;

    return today;
}

int isLeapYear(int year){
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}


bool isSameDate(date d1, date d2){
    return d1.days == d2.days &&
           d1.months == d2.months &&
           d1.years == d2.years;
}


int getMaxDays(int month, int year){
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        case 2:
            if(isLeapYear(year))
                return 29;
            else
                return 28;
    }

    return 0;
}


int compareDate(date d1, date d2) {
    if (d1.years != d2.years)
        return d1.years - d2.years;

    if (d1.months != d2.months)
        return d1.months - d2.months;

    return d1.days - d2.days;
}


date inputDate(){
    date d;
    int maxDays;
    date today=timenow();
    

    do{
        printf("Enter Year: ");
        scanf("%d", &d.years);

    }while(d.years < today.years);


    do{
        printf("Enter Month : ");
        scanf("%d", &d.months);

    } while(d.months < 1 || d.months > 12);

    maxDays = getMaxDays(d.months, d.years);

    do{
        printf("Enter Day (1-%d): ", maxDays);
        scanf("%d", &d.days);

    } while(d.days < 1 || d.days > maxDays);

    return d;
}

int todaydate (date d){
    int total = 0;
    int y = d.years - 1;
    
    total += y * 365 + (y / 4) - (y / 100) + (y / 400);
    
    for(int m = 1; m < d.months; m++){
        total += getMaxDays(m, d.years);
    }
    total += d.days;
    return total;
}


int defferancedate(date d1 , date d2){
    return todaydate(d1)-todaydate(d2);
}

