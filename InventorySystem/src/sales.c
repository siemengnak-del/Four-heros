#include "../include/inventory.h"
#include "../include/globals.h"
#include "../include/memory.h"
#include "../include/date.h"
#include "../include/product.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>





void sellProduct() {

    float totalamount = 0;
    float totalProfit = 0;

    int *storeindex = createSearchArray();

    if(storeindex == NULL){
        return;
    }
    int count = findProduct(storeindex);

    if (count == 0) {
        printf("Product not found\n");
        free(storeindex);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d. ", i + 1);
        displayProduct(storeindex[i]);
    }

    date today = timenow();


    int qty;

    printf("Enter quantity to sell: ");
    scanf("%d", &qty);

    if (qty <= 0) {

        printf("Invalid quantity!\n");
        free(storeindex);
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (compareDate(products[storeindex[j]].expirydate,products[storeindex[j + 1]].expirydate) > 0) {

                int temp = storeindex[j];
                storeindex[j] = storeindex[j + 1];
                storeindex[j + 1] = temp;
            }
        }
    }

    int totalStock = 0;

    for (int i = 0; i < count; i++) {
        if(compareDate(products[storeindex[i]].expirydate, today) >= 0){
            totalStock += products[storeindex[i]].quantity;
        }
    }

    if (qty > totalStock) {
        printf("Not enough stock\n");
        free(storeindex);
        return;
    }

    int originalqty = qty;
    float discount = 0;
    int valid = 0;
    int x;

    printf("Do you have any discount?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Choice: ");
    scanf("%d", &x);

    if(x == 1){

        do{
            printf("Enter discount percentage: ");
            scanf("%f", &discount);

            if(discount < 0 || discount > 100){
                printf("Discount must be between 0 and 100\n");
            }

        }while(discount < 0 || discount > 100);

        valid = 1;
    }
    else if(x == 2){

        discount = 0;
    }
    else{

        printf("Invalid choice!\n");
        free(storeindex);
        return;
    }
    for (int i = 0; i < count && qty > 0; i++) {

        int idx = storeindex[i];

        if (compareDate(products[idx].expirydate, today) < 0) {
            continue; 
        }

        int soldqty;

        if (products[idx].quantity <= qty) {

            soldqty = products[idx].quantity;
            qty -= soldqty;
            products[idx].quantity = 0;

        } else {

            soldqty = qty;
            products[idx].quantity -= qty;
            qty = 0;
        }
        float finalPrice =products[idx].sellingprice *(1 - discount / 100.0);

        totalamount += soldqty * finalPrice;

        totalProfit += soldqty *(finalPrice - products[idx].costprice);
                
        
        


    }
    
    if(saleCount >= salesCapacity){

        int oldCapacity = salesCapacity;

        resizeSales();

        if(salesCapacity == oldCapacity){
            free(storeindex);
            return;
        }
    }

    sales[saleCount].saleid = saleCount + 1;
    strcpy(sales[saleCount].productId, products[storeindex[0]].id);
    if (valid==1){
        sales[saleCount].discount = discount;
    }else{
        sales[saleCount].discount=0;

    }
    sales[saleCount].quantitySold = originalqty;
    sales[saleCount].totalamount = totalamount;
    sales[saleCount].profit = totalProfit;

    date d = timenow();
    sales[saleCount].saledate = d;

    int month = d.months;
    int day = d.days;

    dailySales[month - 1][day - 1] += totalamount;

    saleCount++;

    for (int i = 0; i < productCount; i++) {
        if (products[i].quantity == 0) {

            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }

            productCount--;
            i--;
        }
    }

    printf("\nSale Successful!\n");
    printf("Quantity Sold : %d\n", originalqty);
    if (valid ==1){
        printf("Discount      : %.2f\n", discount);
    }
    
    
    printf("Total Amount  : %.2f\n", totalamount);
    free(storeindex);
}


void viewSaleHistory(){
    if (saleCount==0){
        printf("there is no sale history");
        return;
    }
   

    float total = 0;

    printf("\n--------SALES HISTORY ----------------------\n");

    for(int i = 0; i < saleCount; i++){
        printf("Sale ID: %d\n",sales[i].saleid);
        printf("Product ID: %s\n",sales[i].productId);
        printf("Quantity Sold: %d\n",sales[i].quantitySold);
        printf("Total Amount: %.2f\n",sales[i].totalamount);
        printf("Discount: %.2f%%\n",sales[i].discount);
        printf("Sale Date: %d/%d/%d\n",sales[i].saledate.days,sales[i].saledate.months,sales[i].saledate.years);
        printf("------------------\n");

        total += sales[i].totalamount;
    }

    printf("Total Revenue : %.2f\n", total);
}
