#include <stdio.h>

void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4) {
   
   int tempVal1 = *userVal1;
   *userVal1 = *userVal2;
   *userVal2 = tempVal1;
   
   int tempVal3 = *userVal3;
   *userVal3 = *userVal4;
   *userVal4 = tempVal3;

}

int main(void){
   
   int num1;
   int num2; 
   int num3; 
   int num4;
   scanf("%d", &num1);
   scanf("%d", &num2);
   scanf("%d", &num3);
   scanf("%d", &num4);
   
   SwapValues(&num1, &num2, &num3, &num4);
   printf("%d %d %d %d\n", num1, num2, num3, num4);
   
   return 0;
}
