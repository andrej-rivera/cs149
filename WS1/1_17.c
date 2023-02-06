#include <stdio.h>

int main(void) {
    int baseInt;
    int headInt;

    /* Type your code here. */
    scanf("%d", &baseInt); // Scanner function, takes in input and sets variable
    scanf("%d", &headInt); // %d indicates that the scanner takes in a decimal input
    printf("    %d\n", headInt);
    printf("    %d%d\n", headInt, headInt);

    printf("%d%d%d%d", baseInt, baseInt, baseInt, baseInt);
    printf("%d%d%d\n", headInt, headInt, headInt);

    printf("%d%d%d%d", baseInt, baseInt, baseInt, baseInt);
    printf("%d%d%d%d\n", headInt, headInt, headInt, headInt);

    printf("%d%d%d%d", baseInt, baseInt, baseInt, baseInt);
    printf("%d%d%d\n", headInt, headInt, headInt);

    printf("    %d%d\n", headInt, headInt);
    printf("    %d\n", headInt);
    return 0;
}