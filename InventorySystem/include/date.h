#ifndef DATE_H
#define DATE_H

#include <stdbool.h>
#include "inventory.h"

date timenow();
date inputDate();

int compareDate(date d1, date d2);
int todaydate(date d);
int defferancedate(date d1, date d2);

bool isSameDate(date d1, date d2);
int isLeapYear(int year);
int getMaxDays(int month, int year);

#endif