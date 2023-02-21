/**
 * Lab 4.14 - Convert to reverse binary
 * Description: This program takes in a positive integer as input, and outputs a string of 1's and 0's representing the integer in reverse binary.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>

int main(void) {

   int x;
   scanf("%d", &x); //scan input integer
  
   //algorithm to print out reverse binary. 
   while(x > 0)
   {
      printf("%d", x % 2);
      x = x / 2;
   }
   printf("\n");
   return 0;
}

