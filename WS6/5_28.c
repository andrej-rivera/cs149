#include <stdio.h>

int main(void) {

   char input[51] = {};
   char input2[51] = {};
   int count = 1;
   int palindrome = 1;
   
   scanf("%c", &input[0]);
   for(int i = 1; i < 50; i++){
      scanf("%c", &input[i]);
      count++;
      if(input[i] == '\0'){
         break;
      }
   }
   
   int newCount = 0;
   for(int i = 1; i < count; i++){
      if(input[i] != ' '){
         input2[newCount] = input[i];
         newCount++;
      }
   }
   newCount--;
   
   int left = 0;
   int right = newCount - 1;
   
   while(right > left){
      if(input2[left] != input2[right]){
         palindrome = 0;
         break;
      }
      left++;
      right--;
   }
   
   if(palindrome){
      printf("palindrome: %s\n", input);
   } else{
      printf("not a palindrome: %s\n", input);
   }

}
