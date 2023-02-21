/**
 * Assignment 1 - count of names
 * Description: This program takes in an file path argument from the terminal and reads it. 
 * Given a list of names, it will count all the occurences each name appears.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
 * References:
 * - https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
 * - https://cplusplus.com/reference/cstring/
 * - https://cplusplus.com/reference/cstdio/fgets/
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//This function takes in a string as an input argument
int main(int argc, char *argv[]) {
    
    if(argv[1] == NULL) //edge case, no argument is given
    {
    	return 0;
    }
    
    //Open file
    FILE *textFile;
    textFile = fopen(argv[1], "r");
    if(textFile == NULL) //edge case for when fopen fails to open a file
    {
    	fprintf(stderr, "error: cannot open file\n");
    	return 1;
    }

    //Initialize variables
    char nameArray[100][30]; // create array of 100 names that can be up to 30 characters long
    int i = 0; //line counter
    int currentSize = 0; //reflects the current size of the array
    char string[30]; //variable to hold strings read from fgets

    //This loop will read lines from the text file using fgets and will stop when the file has ended
    while(fgets(string, 30, textFile) != NULL) // loop until end of file
    {
        ++i;
        if(isspace(string[0])) //if whitespace, print to stderror
        {
            fprintf(stderr,"Warning - Line %d is empty\n", i);
            continue;
        }

        //else, check if name is unique & add to array
        int check = 1; //checker for duplicate

        //This loop traverses the nameArray and checks for duplicates
        for(int i = 0; i < currentSize; ++i)
        {
            if(strcmp(string, nameArray[i]) == 0) //if string matches w/ a name in array
            {
                check = 0; //set check to 0
                break; //break out of the loop
            }
        }
        if(check == 1) //if check is still 1 after looping through array, add it to the array
        {
            strcpy(nameArray[currentSize],string);
            currentSize++;
        }
    }

    //This double-loop will check first traverse nameArray, and then reads the text file again to count how many times a name appears
    for(int i = 0; i < currentSize; ++i)
    {
        rewind(textFile); //reset fgets
        int counter = 0;
        while(fgets(string, 30, textFile) != NULL)
        {
            if(strcmp(string, nameArray[i]) == 0) //compares read line to name in array
            {
                counter++;
            }
        }
        nameArray[i][strcspn(nameArray[i], "\n")] = 0; //formatting, removes trailing \n from nameArray[i]
        fprintf(stdout, "%s: %d\n", nameArray[i], counter);
    }


    fclose(textFile);

    return 0;
}
