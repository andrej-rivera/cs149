#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

/* Type your code here */
typedef struct ItemToPurchase {
   char itemName[50];
   int itemPrice;
   int itemQuantity;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase* item);
void PrintItemCost(ItemToPurchase item);

#endif