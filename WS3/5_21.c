/**
 * Lab 5.21 - Contains the Character
 * Description: This program reads an integer, a list of words, and a character. The integer specifies how many words are in a list while the character is the searchCharacter to look for. It will output all words that contain the searchCharacter.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
*/
#include <stdio.h>
#include <string.h>

int main(void) {

   char wordList[20][10]; // array contains 20 words, each contain less than 10 characters
      
   // Read inputs into array
   int numInt;
   scanf("%d ", &numInt); // Find number of inputs
   
   for(int i = 0; i < numInt; ++i)
   {
      scanf("%s ", &wordList[i]);
   }
   
   char searchCharacter;
   scanf("%c", &searchCharacter); // Find search character
   
   // Print all words that contain the searchCharacter
   for(int i = 0; i < numInt; ++i)
   {
      if(strchr(wordList[i], searchCharacter)) //if search character exists in word
      {
         printf("%s," , wordList[i]);
      }
   }
   printf("\n");
   return 0;
}

