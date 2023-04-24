/**
 * Question 5
 * The program compiles and runs like it normally would. When you run valgrind, you will be able to 
 * see that there is a memory leak. The program is incorrect because it assigns the value 0 to 
 * data[100]. The memory we allocated with malloc does not include data[100], so if we assign a 
 * value to data[100], we are basically overwriting something in that memory location. This is not
 * good to do because it could contain valuable information that now has been overwritten.
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    int* data = (int*) malloc(100 * sizeof(int));
    data[100] = 0;
    
    return 0;
}
