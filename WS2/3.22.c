//Zybooks Lab 3.22 - Smallest Number
//By Andre Rivera & Tanisha Damle
#include <stdio.h>

int main(void) {

   /* Type your code here. */
   int intList[3];
   scanf("%d %d %d", &intList[0], &intList[1], &intList[2]);

   int min = intList[0];
   for(int i = 0; i < 3; i++)
   {
      if(intList[i] < min)
         min = intList[i];
   }


   printf("%d\n", min);
   
   return 0;
}
