#ifndef INVENTORY_H
#define INVENTORY_H

#define INITIAL_CAPACITY 10

typedef struct {
    int days;
    int months;
    int years;
} date;

typedef struct {
    char id[10];
    char name[50];
    char category[30];
    float costprice;
    float sellingprice;
    int quantity;
    date expirydate;
} product;

typedef struct {
    int saleid;
    char productId[10];
    int quantitySold;
    float totalamount;
    float discount;
    float profit;
    date saledate;
} sale;

#endif