#ifndef PRODUCT_H
#define PRODUCT_H

#include "globals.h"
#include "inventory.h"



void addProduct();
void viewProducts();
void searchProduct();
int chooseProduct();
void updateProduct();
void deleteProduct();
void restockProduct();
void sellingproducts();
int findProduct(int storeindex[]); 

void sortbyletter();
void mergeDuplicates();
void displayProduct(int index);

#endif