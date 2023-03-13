#include <stdio.h>

void SortArray(int sortingList[], int numVals){
   
   for(int i = numVals - 1; i >= 1; i--){
      for(int j = 1; j <= i; j++){
         if(sortingList[j - 1] < sortingList[j]){
            //swap sortingList[j] and sortingList[j-1]
            int temp = sortingList[j];
            sortingList[j] = sortingList[j - 1];
            sortingList[j - 1] = temp;
         }
      }
   }
   
   for(int i = 0; i < numVals; i++){
      printf("%d,", sortingList[i]);
   }
   printf("\n");

}

int main(void){

   int input[20];
   
   int count;
   scanf("%d", &count);
   
   for(int i = 0; i < count; i++){
      scanf("%d", &input[i]);
   }
   
   //call SortArray function
   SortArray(input, count);
   
   return 0;

}
