/**
 * Lab 5.18 - Output values below an amount
 * Description: This program takes a list of integers as input (first input specifies # of elements and last input specifies upper threshold) and outputs all numbers below or at a specified threshold.  It is assumed that the list will always contain less than 20 integers.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   int numInt; // first input
   int threshold; // last input
   scanf("%d ", &numInt);
   
   // Read inputs into array
   for(int i = 0; i < numInt; ++i)
   {
      scanf("%d ", &userValues[i]);
   }
   
   scanf("%d", &threshold);
   
   //Read array and print numbers less than or equal to threshold.
   for(int i = 0; i < numInt; ++i)
   {
      if(userValues[i] <= threshold)
      {
         printf("%d,", userValues[i]);
      }
   }
   printf("\n");
   
   return 0;
}

