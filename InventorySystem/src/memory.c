#include <stdio.h>
#include <stdlib.h>

#include "../include/inventory.h"
#include "../include/globals.h"
#include "../include/memory.h"

int* createSearchArray() {

    int *storeindex = malloc(productCount * sizeof(int));

    if(storeindex == NULL){
        printf("Memory allocation failed!\n");
        return NULL;
    }

    return storeindex;
}


void initializeMemory() {

    products = malloc(productCapacity * sizeof(product));

    if(products == NULL){
        
        printf("Failed to allocate memory for products\n");
        exit(1);
    }

    sales = malloc(salesCapacity * sizeof(sale));

    if(sales == NULL){
    
        printf("Failed to allocate memory for sales\n");
        exit(1);
    }
    productCapacity = 10;
    salesCapacity = 10;

    productCount = 0;
    saleCount = 0;
}



void resizeProducts() {

    int newproductcapacity=productCapacity * 2;

    product *temp =realloc(products,newproductcapacity * sizeof(product));

    if(temp == NULL){
        printf("Failed to resize products array\n");
        return;
    }

    products = temp;
    productCapacity = newproductcapacity;
}

void resizeSales() {

    int newsalescapacity=salesCapacity * 2;

    sale *temp =realloc(sales,newsalescapacity* sizeof(sale));

    if(temp == NULL){
        printf("Failed to resize sales array\n");
        return;
    }

    sales = temp;
    salesCapacity=newsalescapacity;
}
