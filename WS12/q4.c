/**
 * Question 4
 * The program compiles and runs like it normally would. GDB or valgrind can be used to find a possible
 * memory leak in the program. With valgrind, you will be able to see that there is a memory leak 
 * because the allocated memory is not freed after you have used it.
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    int* myPtr = NULL;
    myPtr = (int*) malloc(sizeof(int));
    *myPtr = 500;
    
    return 0;
}
