/**
 * Lab 4.16 - Varied amount of input data
 * Description: This program takes a list of integers as input (ended with a negative number) and outputs the maximum and average of the list.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>

int main(void) {

   int input;
   int total = 0;
   int count = 0;
   int max = 0;
   
   scanf("%d", &input);
   while(input >= 0) // input data ends w/ negative number
   {
      total += input;
      count++;
      if(max < input) { max = input; } //find the max
      scanf("%d ", &input);
   }
   printf("%d %0.2lf\n", max, (float)total/count); //print the max & average as a formatted float

   return 0;
}

