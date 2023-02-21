/**
 * Lab 5.16 - Output numbers in Reverse
 * Description: This program takes a list of integers as input (first input specifies # of elements) and outputs the integers in reverse
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers
   
   // Read inputs into array
   int numInt;
   scanf("%d ", &numInt);
   for(int i = 0; i < numInt; ++i)
   {
      scanf("%d ", &userVals[i]);
   }
   
   // Read array in reverse & print.
   for(int i = numInt - 1; i >= 0; --i)
   {
      if(userVals[i] != 0) //doesn't print empty (0) spaces)
      {
         printf("%d,", userVals[i]);
      }
   }
   printf("\n");
   
   
   return 0;
}

