//Zybooks Lab 2.32 - Format Output
//By Andre Rivera & Tanisha Damle
#include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;
   
   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);
   
   /* Type your code here. */
   printf("This house is $%d. The change is $%d since last month.", currentPrice, currentPrice - lastMonthsPrice);
   printf("\n");
   printf("The estimated monthly mortgage is $%.6lf.", (currentPrice * 0.051) / 12);
   printf("\n");


   return 0;
}

