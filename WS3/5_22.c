/**
 * Lab 5.22 - Elements in a Range
 * Description: This program takes a list of integers as input (first input specifies # of elements, second to last input specifies lower threshold, and last input specifies upper threshold) and outputs all within the threshold.  It is assumed that the list will always contain less than 20 integers.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>

int main(void) {

   int userValues[20];    // Set of data specified by the user

   int numInt; // first input indicates # of elements
   scanf("%d ", &numInt);

   
   // Read inputs into array
   for(int i = 0; i < numInt; ++i)
   {
      scanf("%d ", &userValues[i]);
   }
      
   // Determine limits   
   int lower; // lower limit
   int upper; // upper limit
   scanf("%d ", &lower);
   scanf("%d ", &upper);
   
   // Print values within limits
   for(int i = 0; i < numInt; ++i)
   {
      if(userValues[i] <= upper && userValues[i] >= lower)
      {
         printf("%d,", userValues[i]);
      }
   }
   printf("\n");

   return 0;
}

