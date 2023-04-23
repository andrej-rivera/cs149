#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <time.h>


    // HASH TABLE STUFF



int main(int argc, char * argv[]) {
    
    // PROC MANAGER STUFF



   //initializing array of char pointers
   int lines = 10;
   //2d string array (dynamic)
   char** inputs = (char**)malloc(sizeof(char*) * lines); 
   
   //reading from stdin
   int i = 0;
   char buf[100];
   while (fgets(buf, 100, stdin) != NULL) {
      
      //remove new line character from string
      if (buf[strlen(buf) - 1] == '\n') {
         buf[strlen(buf) - 1] = '\0'; /* replace newline with null */
      }
      

      
      //reallocate array
      if(i >= lines - 1){
         lines += 10;
         inputs = realloc(inputs, sizeof(char*) * lines);
      }
      
      //add string to dynamic array
      inputs[i] = NULL;
      inputs[i] = (char*)malloc(strlen(buf)+1);
      strcpy(inputs[i], buf);
      i++;
   }
    printf("\n");

    pid_t pid;

    // Loop to run commands
    for (int j = 0; j < i; ++j) {
        if ((pid = fork()) < 0) { // if error forking
            //err_sys("fork error");
            fprintf(stderr, "Fork Failed\n");
            return 1;
        } else if (pid == 0) {  /* child */
            // Grab command & arg
            char * args[30];
            char * temp = strdup(inputs[j]); // temp string so that inputs[j] is not affected

            args[0] = strtok(temp, " ");
            int argIndex = 1;
            while ((args[argIndex] = strtok(NULL, " ")) != NULL) {
                argIndex++;
            }

            // Create output files & set new stdout, stderr
            char filename[30];
            sprintf(filename, "%d", getpid());
            int fdout = open(strcat(filename, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
            sprintf(filename, "%d", getpid());
            int fderr = open(strcat(filename, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);
            dup2(fdout, 1);
            dup2(fderr, 2);

            // Write logs & Execute
            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", j + 1, getpid(), getppid());



            execvp(args[0], args);

            // this part runs if an error is encountered
            fprintf(stderr, "Error running command (invalid): \"%s\"\n", inputs[j]);
            close(fdout);
            close(fderr);

            exit(2);
        }
    }

    int status;

    // Loop that continues until all children are done
    while ((pid = wait(&status)) != -1) {

        // Open output files & write logs
        char filename[30];
        sprintf(filename, "%d", pid);
        int fdout = open(strcat(filename, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
        sprintf(filename, "%d", pid);
        int fderr = open(strcat(filename, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(fdout, 1);
        dup2(fderr, 2);

        fprintf(stdout, "Finished child %d pid of parent %d\n", pid, getpid());

        // Final print statements to .err file
        if (WIFSIGNALED(status)) { // if killed forcefully by signal
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
        } else if (WIFEXITED(status)) { // else if exited normally
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }

        close(fdout);
        close(fderr);
    }
    
    return 0;
}
