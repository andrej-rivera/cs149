#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
   
   pid_t pid;
   
   pid = fork();
   pid = fork();
   
   if(pid < 0){ // error occurred
      fprintf(stderr, "Fork Failed\n");
      return 1;
   }
   
   else if(pid == 0){ // child process
      printf("hello world from PID %d!\n", (int) getpid());
      return 0;
   } 
   
   else if(pid > 0){ // parent process
      wait(NULL);
      printf("hello world from PID %d!\n", (int) getpid());
      return 0;
   }
}
