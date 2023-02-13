//Zybooks Lab 2.29 - Using Math Functions
//By Andre Rivera & Tanisha Damle
#include <stdio.h>
#include <math.h>

int main(void) {
   double x;
   double y;
   double z;

   /* Type your code here. Note: Include the math library above first. */
   scanf("%lf %lf %lf", &x, &y, &z);
   
   printf("%.2lf %.2lf %.2lf %.2lf", pow(x, z), pow(x, pow(y, 2)), fabs(y), sqrt(pow(x * y, z)));
   printf("\n");
   return 0;
}
