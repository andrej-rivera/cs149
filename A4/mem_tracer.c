/**
 * Assignment 4 - mem tracer
 * Description: This program stores command lines in an array and traces memory
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: April 11, 2023
 * Creation date: April 8, 2023
 * References: 
 * - https://www.log2base2.com/data-structures/linked-list/inserting-a-node-at-the-end-of-a-linked-list.html
 * - https://stackoverflow.com/questions/27594992/uninitialized-value-was-created-by-a-heap-allocation
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

/**
 * TRACE_NODE_STRUCT is a linked list of pointers to function identifiers
 * TRACE_TOP is the head of the list is the top of the stack
**/
struct TRACE_NODE_STRUCT {
   char* functionid; 			// ptr to line
   struct TRACE_NODE_STRUCT* next; 	// ptr to next frama
   //int index;
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL; 		// ptr to the top of the stack

/**
 * LINKED_LIST_STRUCT is a linked list of pointers to command line commands
**/
struct LINKED_LIST_STRUCT {
   char* input;
   struct LINKED_LIST_STRUCT* next;
   int index;
};
typedef struct LINKED_LIST_STRUCT LINKED_LIST;


/* --------------------------------*/
/* function PUSH_TRACE */
/*
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do.
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
**/
void PUSH_TRACE(char* p) 	// push p on the stack
{
   TRACE_NODE* tnode;
   static char glob[]="global";
   if (TRACE_TOP==NULL) {

      // initialize the stack with "global" identifier
      TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));
      // no recovery needed if allocation failed, this is only
      // used in debugging, not in production
      if (TRACE_TOP==NULL) {
         printf("PUSH_TRACE: memory allocation error\n");
         exit(1);
      }

      TRACE_TOP->functionid = glob;
      TRACE_TOP->next=NULL;
   }//if

   // create the node for p
   tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

   // no recovery needed if allocation failed, this is only
   // used in debugging, not in production
   if (tnode==NULL) {
      printf("PUSH_TRACE: memory allocation error\n");
      exit(1);
   }//if

   tnode->functionid=p;
   tnode->next = TRACE_TOP; // insert fnode as the first in the list
   TRACE_TOP=tnode; // point TRACE_TOP to the first node
   
}/*end PUSH_TRACE*/


/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE() // remove the op of the stack
{
   TRACE_NODE* tnode;
   tnode = TRACE_TOP;
   TRACE_TOP = tnode->next;
   free(tnode);
}/*end POP_TRACE*/


/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the
stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok:
funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
   int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
   int i, length, j;
   TRACE_NODE* tnode;
   static char buf[100];

   if (TRACE_TOP==NULL) { // stack not initialized yet, so we are
      strcpy(buf,"global"); // still in the `global' area
      return buf;
   }

   /* peek at the depth(50) top entries on the stack, but do not
      go over 100 chars and do not go over the bottom of the
      stack */
   sprintf(buf,"%s",TRACE_TOP->functionid);
   length = strlen(buf); // length of the string so far
   for(i=1, tnode=TRACE_TOP->next; tnode!=NULL && i < depth; i++,tnode=tnode->next) {
      j = strlen(tnode->functionid); 	// length of what we want to add
      if (length+j+1 < 100) { 	// total length is ok
         sprintf(buf+length,":%s",tnode->functionid);
         length += j+1;
      }else 			// it would be too long
         break;
   }
   return buf;
} /*end PRINT_TRACE*/


// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line)
{
   p = realloc(p,t);
   printf("REALLOC: File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, PRINT_TRACE(), p, t);
   return p;
}


// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line)
{
   void* p;
   p = malloc(t);
   printf("MALLOC: File %s, line %d, function %s allocated new memory segment at address %p to size %d\n", file, line, PRINT_TRACE(), p, t);
   return p;
}


// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line)
{
   free(p);
   printf("FREE: File %s, line %d, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);
}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)


// -----------------------------------------
//adds nodes to linked list given the head node of the list, a string, and an index
void add_node(LINKED_LIST** head, char* line, int index) {
   
   PUSH_TRACE("add_node");
   
   //create the node
   LINKED_LIST* tnode = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
   
   //initialize the node
   tnode->input = line;
   tnode->index = index;
   tnode->next = NULL;
   
   //loop through linked list to see where to put tnode
   LINKED_LIST* current = *head;
   if(current == NULL) {  //if head is empty, set the new node to that
      *head = tnode;
   } else { //else add node to end of linked list
      while(current->next != NULL) { //loop to traverse list
         current = current->next;
      }
      current->next = tnode;
   }
   
   POP_TRACE();
   return;
}//end add_node

// ----------------------------------------------
//prints nodes from linked list (recursively)
void print_nodes(LINKED_LIST* head) {
   
   PUSH_TRACE("print_nodes");
   
   //sets the current node to the head
   LINKED_LIST* current = head;

   //loop to find the tail node to stop recursion
   while(current != NULL){
         printf("%d %s", current->index, current->input);
         current = current->next;
   }
   
   POP_TRACE();
   return;
}//end print_nodes

// ------------------------------------------
// allocates, reallocates, and frees memory used from the commands stored in the linked list
void make_extend_array() {
   
   PUSH_TRACE("make_extend_array");
   
   //initializing array of char pointers
   int lines = 10;
   //2d string array (dynamic)
   char** inputs = (char**)malloc(sizeof(char*) * lines); 
   //head of linked list
   LINKED_LIST* head = NULL; 
   
   //reading from stdin
   int i = 0;
   char buf[100];
   while (fgets(buf, 100, stdin) != NULL) {
      
      if (buf[strlen(buf)] == '\n') {
         buf[strlen(buf)] = '\0'; /* replace newline with null */
      }
      
      //reallocate array
      if(i >= lines - 1){
         lines += 10;
         inputs = realloc(inputs, sizeof(char*) * lines);
      }
      
      inputs[i] = NULL;
      inputs[i] = (char*)malloc(100);
      strcpy(inputs[i], buf);
      add_node(&head, inputs[i], i);
      i++;
   }
   
   print_nodes(head);
   
   //free memory
   free(inputs);
   LINKED_LIST* current = head;
   while (current != NULL) {
      LINKED_LIST* temp = current;
      current = current->next;
      free(temp->input);
      free(temp);
   }

   POP_TRACE();
   return;
}


// ----------------------------------------------
// function main
int main()
{
   PUSH_TRACE("main");
   
   // Redirect stdout to memtrace.out file
   FILE *fp = fopen("memtrace.out", "w");
   if (fp == NULL) {
      printf("Error opening file\n");
      return 1;
   }
   dup2(fileno(fp), STDOUT_FILENO);
   setbuf(stdout, NULL);

   make_extend_array();
   
   fclose(fp);
   
   POP_TRACE();
   POP_TRACE();
   
   return(0);
}// end main





