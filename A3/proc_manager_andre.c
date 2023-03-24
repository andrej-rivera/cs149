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

    pid_t	pid;
	int		status;
	printf("%% ");
	
	//loop that takes in inputs
	while (fgets(buf[i], 30, stdin) != NULL) {

		if (buf[i][strlen(buf[i]) - 1] == '\n')
			buf[i][strlen(buf[i]) - 1] = 0; /* replace newline with null */
        
        if ((pid = fork()) < 0) {
			//err_sys("fork error");
		} else if (pid == 0) {		/* child */
		    char* args[2];
            args[0] = strtok(buf[i], " ");
            //args[0][strlen(args[0]) - 1] = 0;
            
		    //args[1] = strtok(buf[i], " ");
		    args[1][strlen(args[1]) - 1] = 0;
		    
		    int fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
		    dup2(fd, 1);
		    
			execvp(args[0], args);
			close(fd);
			fprintf(stderr, "couldn't execute: %s\n", buf[i]);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("err");
        

		i++;
	    printf("%% ");
	}
	
	//Loop to print commands entered
	printf("\nLines entered: ");
	for(int j = 0; j < i; ++j)
    {
        printf("\n%s", buf[j]);
    }
    printf("\n");
}
