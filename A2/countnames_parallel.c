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
#include<sys/wait.h> 
//#include<sys/wait.h>
//This function takes in a string as an input argument
int main(int argc, char *argv[]) {

    if(argv[1] == NULL) //edge case, no argument is given
    {
        return 0;
    }



    // Initialize variables
    struct my_data { // data structure that will store a name and the # of times it appears
        char name[30];
        int count;
    };
    struct my_data namecounts[100]; // array of 100 names & counts

    int i = 0; //line counter
    int currentSize = 0; //reflects the current size of the array
    char string[30]; //variable to hold strings read from fgets


    // Setup pipe
    int fd[2]; // first pipe to send args to children
    if (pipe(fd)==-1) 
    { 
        fprintf(stderr, "Parent-Child Pipe Failed"); 
        return 1; 
    } 
    
    int fd1[2]; // second pipe to get children to send struct back
    if(pipe(fd1)==-1)
    {
    	fprintf(stderr, "Child-Parent Pipe Failed");
    	return 1;
    }
    
    // Setup children processes
    pid_t pid;
  
    for(int i = 1; i < argc; ++i)
    {

	write(fd[1], argv[i], 100);
        pid = fork(); // forks a child

        if(pid < 0) // if fork results in error
        {
            fprintf(stderr, "Pipe Failed");
            return 1;
        }
        else if(pid == 0) // if child process
        {
            break; // break out of loop to prevent forking
        }

    }

    if(pid != 0) // if parent, add up structs and print
    {
    	wait(NULL); // wait for one child to finish
    	
    	char string[30];
    	read(fd1[0], string, 30); // read a name from pipe
    	printf("%s", string);
    	strcpy(namecounts[0].name, string);
    	currentSize++;
        return 0;
    }
    
    // If not parent, run through this process
    //Open file
    FILE *textFile;
    char fileName[100];
    read(fd[0], fileName, 100);
    textFile = fopen(fileName, "r");
    if(textFile == NULL) //edge case for when fopen fails to open a file
    {

        fprintf(stderr, "range: cannot open file\n");
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
	
	// Write name to parent
	write(fd1[1], string, 30);
    }
    printf("Child %d is done! Arg was %s \n", getpid(), fileName);
    fclose(textFile);
    exit(0);

    return 0;
}


