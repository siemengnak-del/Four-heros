#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/inventory.h"
#include "../include/globals.h"
#include "../include/memory.h"
#include "../include/date.h"

#ifdef _WIN32
    #define _STRICMP _stricmp
#else
    #define _STRICMP strcasecmp
#endif

void displayProduct(int index){
    printf("Name:%s \n ID:%s \n Category :%s \n CostPrice:%.2f \n  selling price: %.2f \n Quantity:%d \n expired date:%d/%d/%d\n",products[index].name,products[index].id,products[index].category,
        products[index].costprice, products[index].sellingprice,products[index].quantity,products[index].expirydate.days,products[index].expirydate.months,products[index].expirydate.years);
    printf("-------------------------\n");
}


int findProduct(int storeindex[]){
    int count=0;
    char input[50];
    getchar(); 

    printf("Enter product ID or Name: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; i < productCount; i++){

        if (_STRICMP(products[i].id, input) == 0 || _STRICMP(products[i].name, input) == 0){
            storeindex[count]=i;
            count++;

        }
    }
    return count;
}



int chooseProduct() {

    int *storeindex = createSearchArray();

    if(storeindex == NULL){
        return -1;
    }

    int count = findProduct(storeindex);

    if(count == 0){
        printf("Product not found!\n");
        free(storeindex);
        return -1;
    }

    for(int i = 0; i < count; i++){
        printf("%d.\n", i + 1);
        displayProduct(storeindex[i]);
    }

    int choice;

    if(count > 1){

        printf("Choose product: ");
        scanf("%d", &choice);

        if(choice < 1 || choice > count){
            printf("Invalid choice!\n");
            free(storeindex);
            return -1;
        }

    } else {
        choice = 1;
    }

    int result = storeindex[choice - 1];

    free(storeindex);

    return result;
}







void sortbyletter(){
    product temp;
    for (int j = 0; j < productCount - 1; j++){
        for (int k = 0; k < productCount - j - 1; k++){
            int cmpcate = _STRICMP(products[k].category, products[k+1].category);
            int swap = 0;
            if (cmpcate > 0){
                swap = 1;
            }
            else if (cmpcate == 0 && _STRICMP(products[k].name, products[k+1].name) > 0){
                swap = 1;
            }
            if (swap){
                temp = products[k];
                products[k] = products[k+1];
                products[k+1] = temp;
            }
        }
    }
}




void addProduct(){
    product p;

    getchar();
    printf("Enter name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';
    

    printf("Enter ID: ");
    fgets(p.id, sizeof(p.id), stdin);
    p.id[strcspn(p.id, "\n")] = '\0';
    
    
    printf("Enter category: ");
    fgets(p.category, sizeof(p.category), stdin);
    p.category[strcspn(p.category, "\n")] = '\0';
    

    printf("Enter cost price: ");
    scanf("%f", &p.costprice);
    
    printf("Enter selling price: ");
    scanf("%f", &p.sellingprice);
    if(p.costprice < 0 || p.sellingprice < 0){
        printf("Invalid price!\n");
        return;
    }


    printf("Enter quantity: ");
    scanf("%d", &p.quantity);
    
    if(p.quantity <= 0){
        printf("Invalid quantity!\n");
        return;
    }
    
    if(productCount >= productCapacity){

        int oldCapacity = productCapacity;

        resizeProducts();

        if(productCapacity == oldCapacity){
            return;
        }
    }

    
    products[productCount] = p;
    printf("enter expiry date: \n");
    products[productCount++].expirydate = inputDate();
    
    printf("Product added successfully!\n");

}


void viewProducts(){
    
    sortbyletter();

    printf("----------------PRODUCT LIST----------------- \n ");
    for (int i=0 ; i<productCount; i++){
        printf("%d.Name:%s | ID:%s | Category :%s | CostPrice:%.2f | selling price: %.2f | Quantity:%d | expired date:%d/%d/%d\n",i+1,products[i].name,products[i].id,products[i].category,products[i].costprice,
            products[i].sellingprice,products[i].quantity,products[i].expirydate.days,products[i].expirydate.months,products[i].expirydate.years);
    }
    if(productCount==0){
        printf("No products available.\n");
        return;
    }
   
}

void searchProduct() {

    int *storeindex = createSearchArray();

    if(storeindex == NULL){
        return;
    }

    int count = findProduct(storeindex);

    if(count == 0){
        printf("There isn't product in stock\n");
        free(storeindex);
        return;
    }

    for(int i = 0; i < count; i++){
        printf("%d.", i + 1);
        displayProduct(storeindex[i]);
    }

    free(storeindex);
}


void mergeDuplicates() {
    for (int i = 0; i < productCount; i++) {
        for (int j = i + 1; j < productCount; j++) {

            if (_STRICMP(products[i].id, products[j].id) == 0 && _STRICMP(products[i].name, products[j].name) == 0  && isSameDate(products[i].expirydate,products[j].expirydate) && products[i].costprice == products[j].costprice &&
                products[i].sellingprice == products[j].sellingprice) {

                products[i].quantity += products[j].quantity;

                for (int k = j; k < productCount - 1; k++) {
                    products[k] = products[k + 1];
                }

                productCount--;
                j--;
            }
        }
    }
}

void restockProduct (){
    
    date d;
    int qty;
    float cost,selling;
    int index = chooseProduct();


    if(index == -1){
        return;
    }
    printf("Enter quantity :");
    scanf("%d",&qty);
    if (qty<=0){
        
        printf("quantiy must be greater than 0\n");
        return;
    }
    printf("Enter Expiry date \n");
    d=inputDate(); 
    printf("Enter cost price :");
    scanf("%f",&cost);
    printf("\nEnter selling price:");
    scanf("%f",&selling );
    if (cost<0 || selling<0 ){
        printf("cost and selling price must be greater than 0\n");
        return;
    }
    if (isSameDate(d, products[index].expirydate) && (products[index].costprice==cost) && (products[index].sellingprice==selling)){
        products[index].quantity += qty;
        printf("products have been restock");
    }else{
        
        if(productCount >= productCapacity){

            int oldCapacity = productCapacity;
            resizeProducts();
            if(productCapacity == oldCapacity){
                return;
            }
        }
        strcpy(products[productCount].name,products[index].name);
        strcpy(products[productCount].id,products[index].id);
        strcpy(products[productCount].category,products[index].category);
        products[productCount].costprice=cost;
        products[productCount].sellingprice=selling;
        products[productCount].quantity=qty;
        products[productCount].expirydate=d;
        productCount++;
        printf("the productthat you have been restock have defferent expiry date.new product added");


    }
    mergeDuplicates();

    
}

void updateProduct(){
    int choice ;
    char text[50];
    float price;
    int index = chooseProduct();

    if(index == -1){
        return;
    }

    while (true) {
        printf("Which one do you want to update?\n");
        printf("1. Name\n");
        printf("2. ID\n");
        printf("3. Category\n");
        printf("4. cost price\n");
        printf("5. Selling price\n");
        printf("6. expiry Date\n");
        printf("7. Save & Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf ("Enter new name :");
                getchar();
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                strcpy(products[index].name,text);
                printf("Name updated!\n");
                break;
            case 2: 
                printf ("Enter new ID :");
                getchar();
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                strcpy(products[index].id,text);
                
                printf("ID updated!\n");
                break;
            case 3: 
                printf ("Enter new Category :");
                getchar();
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                strcpy(products[index].category,text);
                printf("Category updated!\n");

                break;
            case 4: 
                printf ("Enter new cost price :");
                scanf("%f",&price);
                if (price<=0){
                    printf("invalid amount\n");
                    break;
                }
                products[index].costprice=price;
                printf("cost price updated!\n");
                break;
            case 5: 
                printf ("Enter new Selling price :");
                scanf("%f",&price);
                if (price<0){
                    printf("invalid amount\n");
                    break;
                }
                products[index].sellingprice=price;
                printf("Selling price updated!\n");
                break;
            case 6: 
                products[index].expirydate = inputDate();
                printf("Expiry date updated!\n");
                break;
            case 7:
                mergeDuplicates();
                viewProducts();
                printf("Updated successfully!\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    }

}


void deleteProduct() {
    int x;
    int index = chooseProduct();

    if(index == -1){
        return;
    }

    printf("Are you sure?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter choice: ");
    scanf("%d", &x);

    switch (x) {
        case 1:
            for (int i = index; i < productCount - 1; i++) {
                products[i] = products[i + 1];
            }
            productCount--;

            printf("Product deleted successfully.\n");
            break;

        case 2:
            printf("Deletion cancelled.\n");
            break;

        default:
            printf("Invalid choice!\n");
    }
}


