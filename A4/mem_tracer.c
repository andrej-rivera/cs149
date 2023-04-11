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

//linked list to store command line commands
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
// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new columns (updated)
int add_column(int** array,int rows,int columns)
{
   PUSH_TRACE("add_column");
   int i;

   for(i=0; i<rows; i++) {
      array[i]=(int*) realloc(array[i],sizeof(int)*(columns+1));
      array[i][columns]=10*i+columns;
   }//for
   POP_TRACE();
      return (columns+1);
}// end add_column


// -----------------------------------------
// function add_row will add an extra row to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new rows (updated)
int add_row(int** array,int rows,int columns) {
   PUSH_TRACE("add_row");
   int i;

   for(i=0; i < columns; i++) {
      array[i] = (int*) realloc(array[i], sizeof(int) * (rows + 1));
      array[i][rows]=10 * i + rows;
   }//for
   
   POP_TRACE();
   return (rows + 1);
}// end add_row

//creates linked list node
LINKED_LIST* create_node(char* line, int index) {
   
   PUSH_TRACE("add_node");
   
   //create the node
   LINKED_LIST* tnode = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
   
   //initialize the node
   tnode->input = line;
   tnode->index = index;
   tnode->next = NULL;
   POP_TRACE();
   return tnode;
}//end create_node

//adds nodes to linked list
void add_node(LINKED_LIST* head, char* line, int index) {
   
   PUSH_TRACE("add_node");
   
   //create the node
   LINKED_LIST* tnode = create_node(line, index);
   
   //initialize the node
   //tnode->input = line;
   //tnode->index = index;
   //tnode->next = NULL;
   
   //set node to head if empty
   LINKED_LIST** current = head;
   if((*current) == NULL) {
      (*head) = tnode;
   } else { //else add node to end of linked list
      while((*current)->next != NULL) {
         (*current) = (*current)->next;
      }
      (*current)->next = tnode;
   }
   POP_TRACE();
   return;
}//end add_node

//prints nodes from linked list
void print_nodes(LINKED_LIST* head) {
   
   PUSH_TRACE("print_nodes");
   
   LINKED_LIST* current = head;
   

   while(current != NULL){
         printf("%d %s", current->index, current->input);
         current = current->next;
   }
   POP_TRACE();
   return;
}//end print_nodes

// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
void make_extend_array()
{
   PUSH_TRACE("make_extend_array");
   int i, j;
   int **array;
   int ROW = 4;
   int COL = 3;

   //make array
   array = (int**) malloc(sizeof(int*)*4); // 4 rows
   for(i=0; i<ROW; i++) {
      array[i]=(int*) malloc(sizeof(int)*3); // 3 columns
      for(j=0; j<COL; j++)
         array[i][j]=10*i+j;
   }//for

   //display array
   for(i=0; i<ROW; i++)
      for(j=0; j<COL; j++)
         printf("array[%d][%d]=%d\n",i,j,array[i][j]);

   // and a new column
   int NEWCOL = add_column(array,ROW,COL);

   // now display the array again
   for(i=0; i<ROW; i++)
      for(j=0; j<NEWCOL; j++)
         printf("array[%d][%d]=%d\n",i,j,array[i][j]);
INKED_LIST* 
   //now deallocate it
   for(i=0; i<ROW; i++)
      free((void*)array[i]);
   free((void*)array);
   POP_TRACE();
   return;
}//end make_extend_array


void make_extend_array2() {
   
   PUSH_TRACE("make_extend_array2");
   
   //char** array = NULL;
   
   //do something w array??
   //LINKED_LIST* nodes = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
   
   //initializing array of char pointers
   int lines = 10;
   char** inputs = (char**)malloc(sizeof(char*) *lines);
   LINKED_LIST* head = NULL;
   
   //reading from stdin
   int i = 0;
   char buf[100];
   while (fgets(buf, 100, stdin) != NULL) {
      if (buf[lines - 1] == '\n') {
         buf[lines - 1] = '\0'; /* replace newline with null */
      }
      
      //do something to store all the lines in the array and linked list
      if(i >= lines){
         lines *= 2;
         inputs = realloc(inputs, sizeof(char*) * lines);
      }
      
      char* in = (char*)malloc(sizeof(char) *(lines+1));
      strcpy(in, buf);
      add_node(&head, in, i);
      inputs[i] = in;

      
      i++;
   }
   print_nodes(head);


   
   //store inputs in linked list
   //create_node();
   
   free(inputs);
   LINKED_LIST* current = head;
   while (current != NULL) {
      LINKED_LIST* temp = current;
      current = current->next;
      free(temp->input);
      free(temp);
   }
   
   
   //print_nodes(head);
   
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

   make_extend_array2();

   POP_TRACE();
   return(0);
}// end main





