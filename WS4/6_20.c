#include <stdio.h>

/* Define your function here */ 
double LapsToMiles(double userLaps) {
   return 0.25 * userLaps;
}

int main(void) {

   /* Type your code here. Your code must call the function.  */
   double numOfLaps;
   scanf("%lf", &numOfLaps);
   double numOfMiles = LapsToMiles(numOfLaps);
   printf("%0.2lf\n", numOfMiles);

   return 0;
}

