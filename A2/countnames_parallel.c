/**
 * Assignment 2 - count of names (parallel)
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

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
//#include<sys/wait.h>
//This function takes in a string as an input argument
int main(int argc, char *argv[]) {

    if(argv[1] == NULL) //edge case, no argument is given
    {
        return 0;
    }

    static int argIndex = 0;

    //Initialize variables
    struct my_data { // data structure that will store a name and the # of times it appears
        char name[30];
        int count = 0;
    };
    struct my_data namecounts[100]; // array of 100 names & counts

    int i = 0; //line counter
    int currentSize = 0; //reflects the current size of the array
    char string[30]; //variable to hold strings read from fgets

    pid_t pid;
    // loop to instantiate children
    for(int i = 1; i < argc; ++i)
    {
        pid = fork(); // forks a child

        if(pid < 0) // if fork results in error
        {
            fprintf(stderr, "Pipe Failed");
            return 1;
        }
        else if(pid = 0) // if child process
        {
            argIndex++; // increment argIndex by 1
            break; // break out of loop to prevent forking
        }

    }

    if(pid != 0) // if parent, do nothing
    {
        return 0;
    }
    //Open file
    FILE *textFile;
    textFile = fopen(argv[argIndex], "r");
    if(textFile == NULL) //edge case for when fopen fails to open a file
    {
        fprintf(stderr, "error: cannot open file\n");
        return 1;
    }

    //This loop will read lines from the text file using fgets and will stop when the file has ended
    while(fgets(string, 30, textFile) != NULL) // loop until end of file
    {
        ++i;
        if(isspace(string[0])) //if whitespace, print to stderror
        {
            fprintf(stderr,"Warning - Line %d is empty\n", i);
            continue;
        }
        string[strcspn(string, "\n")] = 0; //formatting, removes trailing \n from string

        //else, check if name is unique & add to array
        int check = 1; //checker for duplicate

        //This loop traverses the namecounts struct and checks for duplicates
        for(int i = 0; i < currentSize; ++i)
        {
            if(strcmp(string, namecounts[i].name) == 0) //if string matches w/ a name in array
            {
                check = 0; //set check to 0
                namecounts[i].count++; // increment by 1
            }

            if(!check)
                break;
        }
        if(check == 1) //if check is still 1 after looping through array, add it to the array
        {
            strcpy(namecounts[currentSize].name, string); // add to namecounts data structure
            namecounts[currentSize].count++; // increment by 1
            currentSize++;
        }
    }

    for(int i = 0; i < currentSize; ++i)
    {
        printf("%s: %d\n", namecounts[i].name, namecounts[i].count);
    }

    fclose(textFile);

    return 0;
}

