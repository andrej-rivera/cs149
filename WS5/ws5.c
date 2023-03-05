#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
   
   pid_t pid;
   
   for(int i = 0; i < 2; i++){
      pid = fork();
      if(pid < 0){ // error occurred
      fprintf(stderr, "Fork Failed\n");
         exit(1);
      }
	   
      else if(pid == 0){ // child process
         printf("child: hello world from PID %d!\n", (int) getpid());
         return 0;
      } 
	   
      else if(pid > 0){ // parent process
         wait(NULL);
         printf("parent: hello world from PID %d!\n", (int) getpid());
         //return 0;
      }
   }
   
   return 0;
}
