//Zybooks Lab 1.19 - Basic output with variables
//By Andre Rivera & Tanisha Damle
#include <stdio.h>

int main(void) {
    int userNum;

    printf("Enter integer:\n");
    scanf("%d", &userNum);
    /* Type your code here. */
    printf("You entered: %d\n", userNum); //print user input
    printf("%d squared is %d\n", userNum, (userNum * userNum));
    printf("And %d cubed is %d!!\n", userNum, (userNum * userNum * userNum));

    //Second run

    int userNum2;

    printf("Enter another integer:\n");
    scanf("%d", &userNum2);
    printf("%d + %d is %d\n", userNum, userNum2, (userNum + userNum2));
    printf("%d * %d is %d\n", userNum, userNum2, (userNum * userNum2));

    return 0;
}
