/**
 * Worksheet 9 - Parsing Strings (ZyBooks 9.5)
  * Description: This program takes in string inputs by the user.  It parses and splits the string into two strings if it has a comma as a separator.  Otherwise, it will print out an error if there are no commas.  The substrings have their whitespaces removed.
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: March 31, 2023
 * Creation date: March 31, 2023
 **/
#include<stdio.h>
#include <string.h>

int main(void) {

   /* Type your code here. */
   char *stringOne;
   char *stringTwo;
   char bigString[100];
   
   printf("Enter input string:\n");
   while(strcmp(fgets(bigString, 100, stdin), "q\n") != 0)
   {
      // Check if no commas
      if(strchr(bigString, ',') == NULL)
      {
         printf("Error: No comma in string.\n");
         printf("\nEnter input string:\n");
         continue;
      }
      
      // Split string by commas
      stringOne = strtok(bigString, ",");
      stringTwo = strtok(NULL, ",");

      // Loops to remove whitespaces
      int count = 0;
      for(int i = 0; i < strlen(stringOne); i++)
      {
         if(stringOne[i] != ' ')
         {
            stringOne[count] = stringOne[i];
            count++;
         }
      }
      stringOne[count] = '\0';
      
      count = 0;
      for(int i = 0; i < strlen(stringTwo); i++)
      {
         if(stringTwo[i] != ' ')
         {
            stringTwo[count] = stringTwo[i];
            count++;
         }
      }
      stringTwo[count] = '\0';
      
      // Print strings
      printf("First word: %s\n", stringOne);
      printf("Second word: %s\n", stringTwo);
         
      printf("Enter input string:\n");

   }
   return 0;
}
