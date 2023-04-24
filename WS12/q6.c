/**
 * Question 6
 * The program compiles and runs like it normally would. However, when valgrind is used, it says that 
 * there is an error. Before this message, valgrind also says that no memory leak is possible from
 * the program. This is because we allocated and freed data correctly. However, printing after will
 * not print the correct value in most cases because the memory has already been freed. It is better
 * to print before and then free the memory the array takes up. 
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    int* data = (int*) malloc(100 * sizeof(int));
    data[4] = 3;
    free(data);
    printf("The number is: %d\n",data[4]);
    
    return 0;
}
