#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {
 
   /* Type your code here */ 
   
   struct ItemToPurchase item1;
   
   printf("Item 1\n");
   printf("Enter the item name:\n");
   //scanf("%s", &item1.itemName[0]);
   fgets(item1.itemName, 50, stdin);
   //if (item1.itemName[strlen(item1.itemName) - 1] == '\n') {
   item1.itemName[strlen(item1.itemName) - 1] = '\0'; /* replace newline with null */
   //}
   printf("Enter the item price:\n");
   scanf("%d", &item1.itemPrice);
   printf("Enter the item quantity:\n");
   scanf("%d", &item1.itemQuantity);
   printf("\n");
   
   char c = getchar();
   while(c != '\n' && c != EOF) {
      c = getchar();
   }
   
   struct ItemToPurchase item2;
   
   printf("Item 2\n");
   printf("Enter the item name:\n");
   //scanf("%s", &item2.itemName[0]);
   fgets(item2.itemName, 50, stdin);
   item2.itemName[strlen(item2.itemName) - 1] = '\0';
   printf("Enter the item price:\n");
   scanf("%d", &item2.itemPrice);
   printf("Enter the item quantity:\n");
   scanf("%d", &item2.itemQuantity);
   printf("\n");
   
   printf("TOTAL COST\n");
   PrintItemCost(item1);
   PrintItemCost(item2);
   printf("\n");
   printf("Total: $%d\n", (item1.itemPrice * item1.itemQuantity) + (item2.itemPrice * item2.itemQuantity));
   
   return 0;
}