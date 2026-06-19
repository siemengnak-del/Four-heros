#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/inventory.h"
#include "../include/globals.h"
#include "../include/memory.h"
#include "../include/date.h"
#include "../include/product.h"



void profitReport(){
    float totalRevenue = 0;
    float totalProfit = 0;

    printf("\n--------------- PROFIT REPORT ---------------\n");

    for(int i = 0; i < saleCount; i++){
        printf("\nSale ID: %d\n", sales[i].saleid);
        printf("Product ID: %s\n", sales[i].productId);
        printf("Quantity Sold: %d\n", sales[i].quantitySold);
        printf("Revenue: %.2f\n", sales[i].totalamount);
        printf("Profit: %.2f\n", sales[i].profit);

        totalRevenue += sales[i].totalamount;
        totalProfit += sales[i].profit;
    }

    printf("\n---------------------------------------------\n");
    printf("Total Revenue: %.2f\n", totalRevenue);
    printf("Total Profit : %.2f\n", totalProfit);
}


void dailySalesReport(){
    int month;
    int day;

    printf("\n------------- DAILY SALES REPORT -----------------\n");
    printf("Enter Month: ");
    scanf("%d",&month);

    if(month < 1 || month > 12){
        printf("Invalid month!\n");
        return;
    }
    printf("Enter Day: ");
    scanf("%d",&day);
    if(day < 1 || day > 31){
        printf("Invalid day!\n");
        return;
    }

    printf("\nSales on %d/%d\n",day,month);

    printf("Revenue: %.2f\n",dailySales[month-1][day-1]);
}


void monthlySalesReport(){
    int month;
    printf("\n---------MONTHLY SALES REPORT ----------------\n");
    printf("Enter Month: ");
    scanf("%d",&month);
    if(month < 1 || month > 12){
        printf("Invalid month!\n");
        return;
    }
    float total = 0;

    for(int i=0;i<31;i++){
        total += dailySales[month-1][i];
    }
    printf("\nMonth %d Revenue: %.2f\n",month,total);
}

void lowStockReport(){
    int found = 0;
    printf("\n---------- LOW STOCK ----------------\n");

    for(int i=0;i<productCount;i++){
        if(products[i].quantity <= 5){
            displayProduct(i);
            found=1;
        }
    }
    if (found==0) printf("No low stock products.\n");
}

void reportexpiredproduct(){
    date today=timenow();
    int found = 0;
    
    for (int i = 0; i < productCount; i++) {
        if (compareDate(products[i].expirydate,today)<0) {
            displayProduct(i);
            found=1;
        }
    }
    if (found == 0) printf("there is no expired products");
}

void nearexpieyreport(){
    date today = timenow();
    int found = 0;

    for(int i = 0; i < productCount; i++){
        int diff = defferancedate(products[i].expirydate, today);

        if(diff >= 0 && diff <= 30){
            displayProduct(i);

            printf("Days Remaining: %d\n", diff);
            printf("-----------------------\n");

            found = 1;
        }
    }

    if(found == 0){
        printf("No products expiring within 30 days.\n");
    }
}
