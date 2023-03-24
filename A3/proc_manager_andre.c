#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<fcntl.h>

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(int argc, char *argv[]) {

    char buf[100][30]; // buffer that stores 100 commands of length 30 chars
    int i = 0;
	
	//loop that takes in inputs
	while (fgets(buf[i], 30, stdin) != NULL) {

		if (buf[i][strlen(buf[i]) - 1] == '\n')
			buf[i][strlen(buf[i]) - 1] = 0; /* replace newline with null */
        
		i++;
	}
	printf("\n");
	
	pid_t	pid;
	
	//Loop to run commands
	for(int j = 0; j < i; ++j)
    {
        if ((pid = fork()) < 0) { // if error forking
			//err_sys("fork error");
		} 
		else if (pid == 0) {		/* child */
		    char* args[2];
            args[0] = strtok(buf[j], " ");
            //args[0][strlen(args[0]) - 1] = 0;
            
		    args[1] = strtok(buf[j], " ");
		    //args[1][strlen(args[1]) - 1] = 0;
		    
		    char filename[30];
		    sprintf(filename, "%d", getpid());
		    int fdout = open(strcat(filename, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
		    sprintf(filename, "%d", getpid());
		    int fderr = open(strcat(filename, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);
		    dup2(fdout, 1);
		    dup2(fderr, 2);
		    
		    fprintf(fdout, "Starting command %d: child %d pid of parent %d", j + 1, getpid(), getppid());
		    
			execvp(args[0], args);
			fprintf(stdout, "Finished child %d pid of parent %d", getpid(), getppid());
			fprintf(stderr, "Exited with exitcode = %d", exitcode);
			close(fdout);
			close(fderr);
			exit(127);
		}
    }
    
    while (wait ( NULL) != -1) {  }
    printf("All Done!\n");
}
