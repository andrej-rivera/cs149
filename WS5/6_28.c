#include <stdio.h>
#include <string.h>
#include <ctype.h>

void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
   int x = 0;
   for(int i = 0; i < 50; i++){
      if(isalpha(userString[i])){
         userStringAlphaOnly[x] = userString[i];
         x++;
      }
   }
   printf("%s\n", userStringAlphaOnly);
}

int main(void) {
   char input[50] = {};
   int num = 0;
   scanf("%c", &input[0]);
   for(int i = 1; i < 50; i++){
      scanf("%c", &input[i]);
      num++;
      if(input[i] == '\0'){
         break;
      }
   }
   
   char output[50] = {};
   RemoveNonAlpha(input, output);
   
   return 0;
}
