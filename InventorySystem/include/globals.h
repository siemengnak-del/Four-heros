#ifndef GLOBALS_H
#define GLOBALS_H

#include "inventory.h"

extern product *products;
extern int productCount;
extern int productCapacity;

extern sale *sales;
extern int saleCount;
extern int salesCapacity;

extern float dailySales[12][32];

#endif