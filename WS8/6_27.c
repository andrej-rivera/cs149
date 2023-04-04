#include <stdio.h>
#include <string.h>

/* Define your function here */
int CalcNumCharacters(char* userString, char userChar) {
   
   int count = 0;
   for(int i = 0; i < strlen(userString); ++i) {
      
      if(userChar == userString[i]) {
         count++;
      }
   }
   
   return count;
}

int main(void) {
   
   /* Type your code here. */
   
   char search;
   scanf("%c", &search);
   
   char space;
   scanf("%c", &space);
   
   char input[50] = {};
   //scanf("%c", &input[0]);
   for(int i = 0; i < 50; ++i){
      scanf("%c", &input[i]);
      if(input[i] == '\0'){
         break;
      }
   }
   
   int num = CalcNumCharacters(input, search);
   //printf("%d", num);
   
   if(num == 1){
      printf("%d %c\n", num, search);
   } else {
      printf("%d %c's\n", num, search);
   }
   
   return 0;
}



