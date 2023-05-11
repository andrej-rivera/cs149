/**
 * Assignment 6 - countnames threaded
 * Description: This program counts names to employ multi-threading with two threads.
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: May 10, 2023
 * Creation date: May 8, 2023
 - https://sjsu.instructure.com/courses/1560213/files/folder/code/a6?preview=72952745
 - https://www.techiedelight.com/print-current-date-and-time-in-c/
 - https://man7.org/linux/man-pages/man3/pthread_create.3.html
*/
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

// thread mutex lock for access to the log index
// use this mutexlock for mutual exclusion
// when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

// thread mutex lock for critical sections of allocating THREADDATA
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

// thread mutex lock for access to the name counts data structure
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void *thread_runner(void *);
pthread_t tid1, tid2;

// struct points to the thread that created the object.
// This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
  pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA *p = NULL;

// variable for indexing of messages by the logging function.
int logindex = 0;
int *logip = &logindex;

// struct for storing string name & appearance counts
struct NAME_STRUCT
{
  char name[30];
  int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

// node with name_info for a linked list
struct NAME_NODE
{
  THREAD_NAME name_count;
  struct NAME_NODE *next;
};
typedef struct NAME_NODE NAME_NODE;
NAME_NODE *head = NULL;

// find a node in list based on the string name
NAME_NODE *find(char *name, NAME_NODE *start)
{

  NAME_NODE *tmpNext = start;

  // traverse through list
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

// add a node to list given a name
void addNode(char *name)
{
  pthread_mutex_lock(&tlock3);
  NAME_NODE *node = find(name, head);
  if (node == NULL) // if node isn't found, create it & insert it
  {
    node = (NAME_NODE *)malloc(sizeof(NAME_NODE));
    if (node == NULL) // check if malloc worked
      return;

    // insert node into list & assign values
    NAME_NODE *temp = head;
    head = node;
    node->next = temp;
    strcpy(node->name_count.name, name);
    node->name_count.count = 1;
  }
  else // otherwise, increment the count by one
  {
    node->name_count.count++;
  }
  pthread_mutex_unlock(&tlock3);
}

// method to print log messages
void logprint(char *message)
{

  int hour;
  int min;
  int sec;
  int day;
  int month;
  int year;

  time_t timeNow;
  time(&timeNow);

  struct tm *local = localtime(&timeNow);
  hour = local->tm_hour;        // hours since midnight (0-23)
  min = local->tm_min;          // mins passed after the hour (0-59)
  sec = local->tm_sec;          // secs passed after min (0-59)
  day = local->tm_mday;         // day of the month (1-31)
  month = local->tm_mon + 1;    // month of year (0-11)
  year = local->tm_year + 1900; // year since 1900

  pthread_mutex_lock(&tlock1);
  if (hour < 12)
  {
    fprintf(stdout, "Logindex %d, thread %ld, PID, %d, %02d/%02d/%d %02d:%02d:%02d pm: %s", ++logindex, pthread_self(), getpid(), day, month, year, hour, min, sec, message);
  }
  else
  {
    fprintf(stdout, "Logindex %d, thread %ld, PID, %d, %02d/%02d/%d %02d:%02d:%02d am: %s", ++logindex, pthread_self(), getpid(), day, month, year, hour - 12, min, sec, message);
  }
  pthread_mutex_unlock(&tlock1);
}

/*********************************************************
// function main
*********************************************************/
int main(int argc, char *argv[])
{
  // TODO similar interface as A2: give as command-line arguments three filenames of numbers (the numbers in the files are newline-separated).
  
  if(argc != 3) {
     fprintf(stderr, "Exactly two files are not provided.");
     exit(2);
  }
  
  printf("=============================== Log Messages ===============================\n");

  // Create first thread & pass first file as arg
  printf("Create first thread\n");
  pthread_create(&tid1, NULL, thread_runner, argv[1]);

  // Create second thread & pass second file as arg
  printf("Create second thread\n");
  pthread_create(&tid2, NULL, thread_runner, argv[2]);

  // Exit threads
  printf("Wait for first thread to exit\n");
  pthread_join(tid1, NULL);
  printf("First thread exited\n");

  printf("Wait for second thread to exit\n");
  pthread_join(tid2, NULL);
  printf("Second thread exited\n");

  printf("\n=============================== Name Counts  ===============================\n");

  // print all name counts & print them.
  NAME_NODE *current = head;
  while (current != NULL)
  { // loop to traverse list
    printf("%s: %d\n", current->name_count.name, current->name_count.count);
    NAME_NODE *temp = current;
    current = current->next;
    // free linked list node
    free(temp);
  }

  exit(0);

} // end main

/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void *thread_runner(void *x)
{
  pthread_t me;

  me = pthread_self();

  pthread_mutex_lock(&tlock2); // critical section starts
  logprint(" ");
  if (p == NULL)
  { // if THREADDATA doesn't exist, create it
    p = (THREADDATA *)malloc(sizeof(THREADDATA));
    p->creator = me;
  }
  pthread_mutex_unlock(&tlock2); // critical section ends

  if (p != NULL && p->creator == me)
  {
    printf("This is thread %ld and I created THREADDATA %p\n", me, p);
  }
  else
  {
    printf("This is thread %ld and I can access the THREADDATA %p\n", me, p);
  }

  // Open files & start reading
  char *file = (char *)x;
  FILE *names = fopen(file, "r");
  if(names == NULL) {
     printf("Error - cannot open file.");
     exit(2);
  }
  char input[30];
  logprint(" opened file ");
  printf("%s\n", file);

  // Loop to read from file & add to linked list
  int count = 0;
  while (fgets(input, 30, names) != NULL)
  {
    count++;

    if (isspace(input[0])) // if whitespace, print to stderror
    {
      fprintf(stderr, "Warning - file %s line %d is empty\n", file, count);
      continue;
    }

    if (input[strlen(input) - 1] == '\n')
    {
      input[strlen(input) - 1] = '\0'; /* replace newline with null */
    }

    addNode(input); // add name to list
  }
  fclose(names);

  pthread_mutex_lock(&tlock2); // critical section starts

  logprint(" ");
  if (p != NULL && p->creator == me) // if THREADDATA creator
  {
    printf("This is thread %ld and I delete THREADDATA\n", me);

    // Free the THREADATA object.
    free(p);
    p = NULL;
  }
  else
  {
    printf("This is thread %ld and I can access the THREADDATA\n", me);
  }
  pthread_mutex_unlock(&tlock2); // critical section ends

  pthread_exit(NULL);

} // end thread_runner
