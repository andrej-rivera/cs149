/**
 * Assignment 3 - proc manager
 * Description: This program executes multiple commands
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: March 21, 2023
 * Creation date: March 21, 2023
 **/
 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
 
 
//This function takes in a string as an input argument
int main(int argc, char *argv[]) {
    
    int position = 0;
    
    
    int status;
    pid_t pid;
    char string[30];
    
    
    while(fgets(string, 30, stdin) != NULL) {
    
        //removing the trailing new line from string
        if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
        }
        
        position++;
        pid = fork(); // creates a child process

        if(pid < 0) { // if error in fork
            //err_sys("fork error");
            fprintf(stderr, "Fork Failed\n");
            return 1;
        }
        
        else if(pid == 0) { // child process
        
            char *arg[31] = {0};
            arg[0] = strtok(string, " ");
            int argIndex = 1;
            while ((arg[argIndex] = strtok(NULL, " ")) != NULL) {
                argIndex++;
            }
            arg[argIndex] = NULL;
            
            // output and error files
        
            char out_file[30]; // array to hold stdout
            char err_file[30]; // array to hold stderr
            
            sprintf(out_file, "%d.out", getpid());
            sprintf(err_file, "%d.err", getpid());
            
            //open log files
            int fdout = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            dup2(fdout, 1);
            int fderr = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            dup2(fderr, 2);
            
            fprintf(stdout,"Starting command %d: child %d pid of parent %d\n", position, getpid(), getppid());
            fflush(stdout);
            
            //check if execvp ran properly
            if(execvp(arg[0], arg) == -1){
                perror(arg[0]);
                exit(2);
            } else {
                execvp(arg[0], arg);
            }
            
            // Write logs & Execute
      //      fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", i, getpid(), getppid());

            //debug logs
            //fprintf(stdout, "%s\n", buf[j]); 
            //fprintf(stdout, "arg 1 = %s\narg 2 = %s\n", args[0], args[1]);

            //execvp(args[0], args);

            
        }
    }  
    
    // parent process
        
    int count = 0;
    while((pid = wait(&status)) > 0) {
        
        char out_file[30]; // array to hold stdout
        char err_file[30]; // array to hold stderr

        //push the logs to the files
        sprintf(out_file, "%d.out", pid);
        sprintf(err_file, "%d.err", pid);

        //open log files
        int fdout = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fdout, 1);
        
        int fderr = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fderr, 2);
 	
 	fprintf(stdout, "Finished child %d pid of parent %d\n", pid, getpid());
	//fflush(stdout);

        //normal termination with an exit code
        if (WIFEXITED(status)) {
            
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }
        //abnormal termination with an exit code
        else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        }
                
        count++;
    }
        
        
        
        
    
    
    
    



    return 0;



}