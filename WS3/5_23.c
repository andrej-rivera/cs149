/**
 * Lab 5.23 - Two Smallest Numbers
 * Description: This program takes a list of integers as input (first input specifies # of elements) and the two smallest integers.  It is assumed that the list will always contain at least 2 integers and less than 20 integers.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>
#include <limits.h>
int main(void) {

   int userValues[20];    // Set of data specified by the user

   int numInt; // first input indicates # of elements
   int smallest = INT_MAX; // Smallest integer
   int smallestIndex; // index to keep track of smallest number
   int secondSmallest = INT_MAX; // Second smallest integer
   scanf("%d ", &numInt);
   
   // Read inputs into array & set smallest
   for(int i = 0; i < numInt; ++i)
   {
      scanf("%d ", &userValues[i]);
      if(smallest > userValues[i]) // Set new Smallest
      {
         smallest = userValues[i];
         smallestIndex = i;
      }
   }
   
   // Reiterate through array to find second smallest
   for(int i = 0; i < numInt; ++i)
   {
      if(secondSmallest > userValues[i] && i != smallestIndex) // Set secondSmallest value (doesn't look at smallest for comparison)
      {
         secondSmallest = userValues[i];
      }
   }   
      
   printf("%d and %d\n", smallest, secondSmallest);

   return 0;
}

