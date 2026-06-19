#include <stdio.h>
#include <stdlib.h>

#include "include/inventory.h"
#include "include/date.h"
#include "include/globals.h"
#include "include/memory.h"
#include "include/product.h"
#include "include/report.h"
#include "include/sales.h"




void displayMainMenu(){
    printf("\n-----------MAIN HUB-------------\n");
    printf("1. Inventory Management \n");
    printf("2. Sales & Checkout Operations\n");
    printf("3. Reports\n");
    printf("0. Shutdown System\n");
    printf("----------------------------------------------\n");
}
void InventoryMenu() {
    int choice;
    while(1) {
        printf("\n--- INVENTORY MANAGEMENT  ---\n");
        printf("1. Add New Product\n");
        printf("2. View Product Catalog\n");
        printf("3. Search Product Details\n");
        printf("4. Restock Existing Product\n");
        printf("5. Update Product Information\n");
        printf("6. Delete Product Record\n");
        printf("0. Return to Main Hub\n");
        printf("-----------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: restockProduct(); break;
            case 5: updateProduct(); break;
            case 6: deleteProduct(); break;
            case 0: return; // Exits loop back to main menu
            default: printf("Invalid option!\n");
        }
    }
}

void SalesMenu() {
    int choice;
    while(1) {
        printf("\n--- SALES & CHECKOUT OPERATIONS ---\n");
        printf("1. Sales\n");
        printf("2. View Sales History\n");
        printf("0. Return to Main Hub\n");
        printf("-----------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: sellProduct(); break;
            case 2: viewSaleHistory(); break;
            case 0: return; 
            default: printf("Invalid option!\n");
        }
    }
}

void ReportsMenu() {
    int choice;
    while(1) {
        printf("\n-----------REPORTS ---------------\n");
        printf("1. Low Stock Alert Audit\n");
        printf("2. Profitability Margin Report\n");
        printf("3. Daily Revenue Breakdown\n");
        printf("4. Monthly Revenue Breakdown\n");
        printf("5. Manual Expired Stock Check\n");
        printf("6. Manual 30-Day Expiry Run\n");
        printf("0. Return to Main Hub\n");
        printf("------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: lowStockReport(); break;
            case 2: profitReport(); break;
            case 3: dailySalesReport(); break;
            case 4: monthlySalesReport(); break;
            case 5: reportexpiredproduct(); break;
            case 6: nearexpieyreport(); break;
            case 0: return; 
            default: printf("Invalid option!\n");
        }
    }
}


int main(){
    int choice;

    initializeMemory(); 

    printf("Initializing System... Running Expiry Diagnostics:\n");
    reportexpiredproduct();  
    nearexpieyreport();     
    lowStockReport() ;
    printf("----------------------------------------------------------\n");

    while(1)
    {
        displayMainMenu();
        printf("Enter option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input type! Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch(choice)
        {
            case 1: InventoryMenu(); break; 
            case 2: SalesMenu(); break;     
            case 3: ReportsMenu(); break;   
            case 0:
                if (products != NULL) free(products);
                if (sales != NULL) free(sales);
                printf("System allocations cleared successfully. Goodbye!\n");
                return 0;
            default:
                printf("Invalid selection. Please choose 0-3.\n");
                break;
        }
    }
    return 0;
}
