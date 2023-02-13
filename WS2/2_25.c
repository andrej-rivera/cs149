//Zybooks Lab 2.25 - Divide by X
//By Andre Rivera & Tanisha Damle
#include <stdio.h>

int main(void) {

   /* Type your code here. */
   int userNum; //create reference for integer userNum
   int x; //create reference for integer x
   scanf("%d %d", &userNum, &x); //scan inputs (separated w/ space)
   
   userNum = userNum / x; //divide by x
   printf("%d ", userNum); //print userNum
   
   userNum = userNum / x; //divide by x
   printf("%d ", userNum); //print userNum
   
   userNum = userNum / x; //divide by x
   printf("%d\n", userNum); //print userNum

   return 0;
}
