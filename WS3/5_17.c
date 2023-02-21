/**
 * Lab 5.17 - Middle Item
 * Description: This program takes a list of integers as input (ended by a negative #) and outputs the middlemost item. The list should not exceed 9 numbers.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   //Read integers into array
   int input;
   int count = 0;
   scanf("%d", &input);
   
   while(input >= 0 && count <= 9) // input data ends w/ negative number
   {
      userValues[count] = input;
      count++;
      scanf("%d ", &input);
   }
   
   //edge case for too many numbers (exceed limit of 9)
   if(count > 9)
   {
      printf("Too many numbers\n");
      return 0;
   }
   
   //output middle number in the array
   int middle = count / 2; //middle index
   printf("Middle item: %d\n", userValues[middle]);
   return 0;
}

