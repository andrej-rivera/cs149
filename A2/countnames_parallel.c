 /**
 * Assignment 2 - count of names parallel
 * Description: This program takes in one or more input files on the command line and reads it. 
 * Given a list of names, it will count all the occurences each name appears in a parallel fashion
 * using multiple processes.
 * Author names: Andre Rivera, Tanisha Damle 
 * Author emails: andre.rivera@sjsu.edu, tanisha.damle@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/19/23
 * References:
 * - https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
 * - https://cplusplus.com/reference/cstring/
 * - https://cplusplus.com/reference/cstdio/fgets/
 * - https://stackoverflow.com/questions/47356860/c-how-to-detect-eof-in-pipe-when-reading-only-single-char
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h> 
//This function takes in a string as an input argument
int main(int argc, char *argv[]) {

    if(argv[1] == NULL) //edge case, no argument is given
    {
        return 0;
    }



    // Setup struct
    struct my_data { // data structure that will store a name and the # of times it appears
        char name[30];
        int count;
    };
    struct my_data namecounts[100]; // array of 100 names & counts

    // Setup pipe
    int fd1[2]; // pipe to get children to send struct back
    if(pipe(fd1)==-1)
    {
    	fprintf(stderr, "Child-Parent Pipe Failed");
    	return 1;
    }
    
    // Setup children processes
    pid_t pid;
    int argIndex = 1; // index that marks what argument to pass to child
    
    for(int i = 1; i < argc; ++i)
    {
        pid = fork(); // forks a child

        if(pid < 0) // if fork results in error
        {
            fprintf(stderr, "Pipe Failed");
            return 1;
        }
        else if(pid == 0) // if child process
        {
            close(fd1[0]); // close reading side from child-parent pipe (child writes)
            break; // break out of loop to prevent forking
        }
        argIndex++;  // increment index for next child
    }

    // if parent, add up structs and print
    if(pid > 0) 
    {
        close(fd1[1]); // close writing side from child-parent pipe (parent reads)
    	wait(NULL); // wait for one child to finish
    	
        struct my_data pipedStruct; // struct to store read namecounts
    	int size = 0;  // current size of namecounts
    	int bytesRead = sizeof(pipedStruct); // read will return != 30, if pipe reaches the end
    	
    	while((bytesRead = read(fd1[0], &pipedStruct, sizeof(pipedStruct))) == sizeof(pipedStruct)) // loop until pipe is empty
    	{
    	    //printf("%s", string);
 
            // add read string to struct
    	    int check = 1; //checker for duplicate
    	    
            //This loop traverses the namecounts struct and checks for duplicates
            for(int i = 0; i < size; ++i)
            {
                if(strcmp(pipedStruct.name, namecounts[i].name) == 0) //if string matches w/ a name in array
                {
                    check = 0; //set check to 0
                    namecounts[i].count += pipedStruct.count; // add count
                }

                if(!check)
                   break;
           }
           if(check) //if check is still 1 after looping through array, add it to the array
           {
               strcpy(namecounts[size].name, pipedStruct.name); // copy over name
               namecounts[size].count = pipedStruct.count; // set count
               size++;
           }
    	}
    	
    	//printf("size of array is %d\n", size);
        for(int i = 0; i < size; ++i)
        {
            fprintf(stdout, "%s: %d\n", namecounts[i].name, namecounts[i].count);
        }

        return 0;
    }
   
    // If not parent, run through this process
    
    //Open file
    FILE *textFile;
    textFile = fopen(argv[argIndex], "r");
    if(textFile == NULL) //edge case for when fopen fails to open a file
    {

        fprintf(stderr, "range: cannot open file %s\n", argv[argIndex]);
        exit(1);
        
    }
    
    //loop vars
    int i = 0; //line counter
    char string[30]; //variable to hold strings read from fgets
    int size = 0; // size of namecounts
    
    //This loop will read lines from the text file using fgets and will stop when the file has ended
    while(fgets(string, 30, textFile) != NULL) // loop until end of file
    {
        ++i;
        if(isspace(string[0])) //if whitespace, print to stderror
        {
            fprintf(stderr,"Warning - file %s line %d is empty\n", argv[argIndex], i);
            continue;
        }
        string[strcspn(string, "\n")] = 0; //formatting, removes trailing \n from string
        
        //This loop traverses the namecounts struct and checks for duplicates
        int check = 1; //checker for duplicate
        for(int i = 0; i < size; ++i)
        {
            if(strcmp(string, namecounts[i].name) == 0) //if string matches w/ a name in array
            {
                //printf("%s at %d\n", string, namecounts[i].count);
                check = 0; //set check to 0
                namecounts[i].count++; // increment by 1
            }

            if(!check)
               break;
       }
       
       if(check) //if check is still 1 after looping through array, add it to the array
       {
           strcpy(namecounts[size].name, string); // add to namecounts data structure
           namecounts[size].count = 0; // first, initialize to 0 in case of junk
           namecounts[size].count++; // increment by 1
           size++;
       }

    }
    
    //fprintf(stdout ,"Child %d is done! Arg was %s \n", getpid(), argv[argIndex]);
    
    //This loop will write every struct in namecounts to the pipe
    for(int i = 0; i < size; ++i)
    {
        write(fd1[1], &namecounts[i], sizeof(namecounts[i])); // write entire struct to pipe
    }

    fclose(textFile);
    exit(0);
}


