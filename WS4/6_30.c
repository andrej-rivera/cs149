#include <stdio.h>

/* Define your function here */ 
int MaxNumber(int num1, int num2, int num3, int num4) {
   int nums[] = {num1, num2, num3, num4};
   int max = nums[0];
   for(int i = 1; i < 4; ++i) {
      if(nums[i] > max) {
         max = nums[i];
      }
   }
   return max;
}

int MinNumber(int num1, int num2, int num3, int num4) {
   int nums[] = {num1, num2, num3, num4};
   int min = nums[0];
   for(int i = 1; i < 4; ++i) {
      if(nums[i] < min) {
         min = nums[i];
      }
   }
   return min;
}

int main(void) {

   /* Type your code here. Your code must call the function.  */
   int num1; 
   int num2; 
   int num3; 
   int num4;
   
   scanf("%d", &num1);
   scanf("%d", &num2);
   scanf("%d", &num3);
   scanf("%d", &num4);
   
   int theMax = MaxNumber(num1, num2, num3, num4);
   int theMin = MinNumber(num1, num2, num3, num4);
   
   printf("Maximum is %d\n", theMax);
   printf("Minimum is %d\n", theMin);

   return 0;
}

