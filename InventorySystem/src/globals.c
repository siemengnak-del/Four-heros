#include <stdio.h>
#include <stdlib.h>

#include "../include/inventory.h"
#include "../include/globals.h"


product *products = NULL;
int productCount = 0;
int productCapacity = 10;

sale *sales = NULL;
int saleCount = 0;
int salesCapacity = 10;

float dailySales[12][32]={0};