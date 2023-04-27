/**
 * Assignment 5 - proc manager
 * Description: This program executes multiple commands with a timer by keeping track of their duration, and restarts processes
 * that take too long, and stores processes in a hash table.
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: March 24, 2023
 * Creation date: March 21, 2023
 - https://linux.die.net/man/3/clock_gettime
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <time.h>
#include  <errno.h>


// HASH TABLE STUFF
struct nlist //DONE
{                       /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *command;         // command
    struct timespec startTime; // time the command started
    struct timespec endTime; // time the command ended
    int index; // line index inside input text file
    pid_t pid; // pid of process (identifier), can use pid result of wait for lookup 
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */


/* This is the hash function: form hash value for string s */
/* TODO change to: unsigned hash(int pid) */
/* TODO modify to hash by pid. */
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(pid_t pid) //DONE
{
    unsigned hashval = pid % HASHSIZE;
    return hashval;
}


/* lookup: look for s in hashtab */
/* TODO change to lookup by pid: struct nlist *lookup(int pid) */
/* TODO modify to search by pid, you won't need strcmp anymore */
/* This is traversing the linked list under a slot of the hash
table. The array position to look in is returned by the hash
function */
struct nlist *lookup(pid_t pid) //DONE
{
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next)
        if (np->pid == pid)
            return np; /* found */
    return NULL;       /* not found */

}


/* insert: put (name, defn) in hashtab */
/* TODO: change this to insert in hash table the info for a new
pid and its command */
/* TODO: change signature to: struct nlist *insert(char *command,
int pid, int index). */
/* This insert returns a nlist node. Thus whtableen you call insert in
your main function */
/* you will save the returned nlist node in a variable (mynode).
    */
/* Then you can set the starttime and finishtime from your main
function: */
/* mynode->starttime = starttime; mynode->finishtime = finishtime;
    */
struct nlist *insert(char *command, pid_t pid, int index) //DONE-ish? (possibly work on this more later)
{
    struct nlist *np;
    unsigned hashval;
    // TODO change to lookup by pid. There are 2 cases:

    /* case 1: the pid is not
    found, so you have to create it with malloc. Then you want to set
    the pid, command and index */
    if ((np = lookup(pid)) == NULL)
    { 
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL) //checks if malloc worked
            return NULL;
        np->pid = pid; //sets pid of entry
        np->index = index; //sets index of entry
        hashval = hash(pid); 
        if ((np->command = strdup(command)) == NULL) //sets command of entry, returns null if error occurs
            return NULL;

        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } 

    return np;
}

int main(int argc, char * argv[]) {

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
    int j;
    // Loop to run commands
    for (j = 0; j < i; ++j) {
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

        //set timer, add proc to table
        struct nlist *node = insert(inputs[j], pid, j); // insert cmd into hashtable
        clock_gettime(CLOCK_MONOTONIC, &node->startTime); // record the start time
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
        
        struct nlist *node = lookup(pid); // lookup node
        clock_gettime(CLOCK_MONOTONIC, &node->endTime); // record end time
        
        // Calculate duration of node using stored values
        double duration = (node->endTime.tv_sec - node->startTime.tv_sec);
        duration += (node->endTime.tv_nsec - node->startTime.tv_nsec) / 1000000000.0;
        
        // Final print statements to .err file
        if (WIFSIGNALED(status)) { // if killed forcefully by signal
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
            if(duration <= 2) { // proc_manager will not restart process
                fprintf(stderr, "spawning too fast\n");
            }
        } else if (WIFEXITED(status)) { // else if exited normally
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            if(duration <= 2) { // proc_manager will not restart process
                fprintf(stderr, "spawning too fast\n");
            }
        }
        
        //printing to stdout files
        fprintf(stdout, "Finished child %d pid of parent %d\n", pid, getpid());
        fprintf(stdout, "Finished at %ld, runtime duration %f\n", node->endTime.tv_sec, duration);

        if(duration > 2) //if duration > 2, restart process
        {
            char * temp = strdup(node->command); // temp string so that node->command is not affected

            //fork child
            pid = fork();
            //if error forking
            if(pid < 0){
               fprintf(stderr, "Fork Failed\n");
               return 1;
            }
            
            else if(pid == 0) {//child process
               
               // Create output files & set new stdout, stderr
               char filename[30];
               sprintf(filename, "%d", getpid());
               int fdout = open(strcat(filename, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
               sprintf(filename, "%d", getpid());
               int fderr = open(strcat(filename, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);
               dup2(fdout, 1);
               dup2(fderr, 2);
               
               // Grab command & arg
               char * args[30];

               args[0] = strtok(temp, " ");
               int argIndex = 1;

               while ((args[argIndex] = strtok(NULL, " ")) != NULL) {
                   argIndex++;
               }

               //write restarting to stdout and stderr files
               fprintf(stdout, "RESTARTING\n");
               fprintf(stderr, "RESTARTING\n");

               // Write logs & Execute
               fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", node->index + 1, getpid(), getppid());

               execvp(args[0], args);

               // this part runs if an error is encountered
               perror("execvp\n");
               fprintf(stderr, "Error running command (invalid): \"%s\"\n", temp);
               close(fdout);
               close(fderr);

               exit(2);
               
            }
            
            else if(pid > 0) { // parent
               // add to hash table
               struct nlist *node = insert(temp, pid, ++j); // insert command into hashtable
               clock_gettime(CLOCK_MONOTONIC, &node->startTime); //record start time
               
            }
        }

        close(fdout);
        close(fderr);
    }
    
    return 0;
}
