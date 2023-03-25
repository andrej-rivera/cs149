/**
 * Assignment 3 - proc manager
 * Description: This program executes multiple commands
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: March 24, 2023
 * Creation date: March 21, 2023
 * References: 
 * - https://stackoverflow.com/questions/56845395/parsing-command-line-arguments-for-shell
 * - https://man7.org/linux/man-pages/man2/dup.2.html
 * - https://pubs.opengroup.org/onlinepubs/7908799/xsh/wait.html
 * - https://stackoverflow.com/questions/58745646/is-there-any-way-to-figure-out-that-child-process-was-killed-with-sigkill-by-the
 **/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(int argc, char * argv[]) {

    char buf[100][30]; // buffer that stores 100 commands of length 30 chars
    int i = 0;

    // Loop that takes in inputs (loops until EOF or ctrl-D is signalled)
    while (fgets(buf[i], 30, stdin) != NULL) {
        if (buf[i][strlen(buf[i]) - 1] == '\n')
            buf[i][strlen(buf[i]) - 1] = 0; /* replace newline with null */

        i++;
    }
    printf("\n");

    pid_t pid;

    // Loop to run commands
    for (int j = 0; j < i; ++j) {
        if ((pid = fork()) < 0) { // if error forking
            //err_sys("fork error");
        } else if (pid == 0) {  /* child */
            // Grab command & arg
            char * args[30];
            char * temp = strdup(buf[j]); // temp string so that buf[j] is not affected

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

            //debug logs
            //fprintf(stdout, "%s\n", buf[j]); 
            //fprintf(stdout, "arg 1 = %s\narg 2 = %s\n", args[0], args[1]);

            execvp(args[0], args);

            // this part runs if an error is encountered
            fprintf(stderr, "Error running command (invalid): \"%s\"\n", buf[j]);
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
        } else { // else if exited normally
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }

        close(fdout);
        close(fderr);
    }
}
