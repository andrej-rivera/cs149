#include <stdio.h>
#include <string.h>

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
   
   int count = 0;
   for(int i = 0; i < num; i++){
      if(input[i] == ' ' || input[i] == '.' || input[i] == '!' || input[i] == ','){
         continue;;
      }
      count++;
   }
   
   printf("%d\n", count);
   
   return 0;
}
