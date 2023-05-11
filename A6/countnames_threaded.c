#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include<unistd.h>

/*****************************************
//CS149 SP23
//Template for assignment 6
//San Jose State University
//originally prepared by Bill Andreopoulos
*****************************************/


//thread mutex lock for access to the log index
//TODO you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;


//thread mutex lock for critical sections of allocating THREADDATA
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER; 


//thread mutex lock for access to the name counts data structure
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER; 


void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object. 
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
  pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p=NULL;


//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;


//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole array.
//You can use a linked list template from A5. You should also consider using a hash table, like in A5 (even faster).
struct NAME_STRUCT
{
  char name[30];
  int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

//array of 100 names
THREAD_NAME names_counts[100];

//node with name_info for a linked list
struct NAME_NODE
{
  THREAD_NAME name_count;
  struct NAME_NODE *next;
};
typedef struct NAME_NODE NAME_NODE;
NAME_NODE *head = NULL;

//find a command based on the pid
NAME_NODE *find(char *name)
{
  NAME_NODE *tmpNext = head;
  
  //traverse through list
  while (tmpNext != NULL)
  {
      if (strcmp(tmpNext->name_count.name, name) == 0)
      {
          return tmpNext;
      }
      tmpNext = tmpNext->next;
  }
  return NULL;
}

//add a node given a name
void addNode(char *name)
{
    pthread_mutex_lock(&tlock3);
    NAME_NODE *node = find(name);
    if(node == NULL) // if node isn't found, create it & insert it
    {
        node = (NAME_NODE *)malloc(sizeof(NAME_NODE));
        if(node == NULL) // check if malloc worked
            return;

        //insert node into list & assign values
        NAME_NODE *temp = head;
        head = node;
        node->next = temp;
        strcpy(node->name_count.name, name);
        node->name_count.count = 1;
    }
    else // otherwise, increment the count by one
    {
        pthread_mutex_lock(&tlock3);
        node->name_count.count++;
        pthread_mutex_lock(&tlock3);
    }
    pthread_mutex_unlock(&tlock1);
}

void logprint(char* message) {
   
   int hour;
   int min; 
   int sec;
   int day;
   int month;
   int year;
   
   time_t timeNow;
   time(&timeNow);
   
   struct tm* local = localtime(&timeNow);
   hour = local->tm_hour;			//hours since midnight (0-23)
   min = local->tm_min;				//mins passed after the hour (0-59)
   sec = local->tm_sec;				//secs passed after min (0-59)
   day = local->tm_mday;			//day of the month (1-31)
   month = local->tm_mon+1;			//month of year (0-11)
   year = local->tm_year + 1900;		//year since 1900
   
   pthread_mutex_lock(&tlock1);
   if(hour < 12) {
      fprintf(stdout, "Logindex %d, thread %ld, PID, %d, %02d/%02d/%d %02d:%02d:%02d pm: %s\n", ++logindex, pthread_self(), getpid(), day, month, year, hour, min, sec, message);
   } else {
      fprintf(stdout, "Logindex %d, thread %ld, PID, %d, %02d/%02d/%d %02d:%02d:%02d am: %s\n", ++logindex, pthread_self(), getpid(), day, month, year, hour-12, min, sec, message);
   }
   pthread_mutex_unlock(&tlock1);
}

/*********************************************************
// function main 
*********************************************************/
int main(int argc, char *argv[])
{
  //TODO similar interface as A2: give as command-line arguments three filenames of numbers (the numbers in the files are newline-separated).

  printf("create first thread");
  pthread_create(&tid1,NULL,thread_runner,argv[1]);
  
  printf("create second thread");
  pthread_create(&tid2,NULL,thread_runner,argv[2]);
  
  printf("wait for first thread to exit");
  pthread_join(tid1,NULL);
  printf("first thread exited");

  printf("wait for second thread to exit");
  pthread_join(tid2,NULL);
  printf("second thread exited");

  //TODO print out the sum variable with the sum of all the numbers

  exit(0);

}//end main


/**********************************************************************
// function thread_runner runs inside each thread 
**********************************************************************/
void* thread_runner(void* x)
{
  pthread_t me;

  me = pthread_self();
  printf("This is thread %ld (p=%p)",me,p);
  
  pthread_mutex_lock(&tlock2); // critical section starts
  if (p==NULL) {
    p = (THREADDATA*) malloc(sizeof(THREADDATA));
    p->creator=me;
  }
  pthread_mutex_unlock(&tlock2);  // critical section ends

  if (p!=NULL && p->creator==me) {
    printf("This is thread %ld and I created THREADDATA %p",me,p);
  } else {
    printf("This is thread %ld and I can access the THREADDATA %p",me,p);
  }


  /**
   * //TODO implement any thread name counting functionality you need. 
   * Assign one file per thread. Hint: you can either pass each argv filename as a thread_runner argument from main.
   * Or use the logindex to index argv, since every thread will increment the logindex anyway 
   * when it opens a file to print a log message (e.g. logindex could also index argv)....
   * //Make sure to use any mutex locks appropriately
   */
   char* file = (char*) x;
   FILE* names = fopen(file, "r");
   char buf[100];
   char* input = NULL;
   logprint(input);
   
   //thread to read from file and create the linked list
    pthread_mutex_lock(&tlock3);
    
    
    int count = 0; 
    while(fgets(input, 100, names) != NULL) {
       count++;
       
       //char* in = NULL;
       
       if (input[strlen(input) - 1] == '\n') {
         input[strlen(input) - 1] = '\0'; /* replace newline with null */
       }
       
        addNode(input);
       
    }
    fclose(names);
    //logprint(file);
    pthread_mutex_unlock(&tlock3);

  // TODO use mutex to make this a start of a critical section 
  // critical section starts
  pthread_mutex_lock(&tlock2); // critical section starts
  if (p!=NULL && p->creator==me) {
    printf("This is thread %ld and I delete THREADDATA", me);
    
    
    //
    
  /**
   * TODO Free the THREADATA object.
   * Freeing should be done by the same thread that created it.
   * See how the THREADDATA was created for an example of how this is done.
   */
   logprint(input);
   free(p);
   p = NULL;
   
  } else {
    printf("This is thread %ld and I can access the THREADDATA",me);
  }
  // TODO critical section ends
  pthread_mutex_unlock(&tlock2); // critical section ends

  pthread_exit(NULL);
  //return NULL;

}//end thread_runner

