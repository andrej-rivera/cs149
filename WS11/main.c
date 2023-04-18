/**
 * Worksheet 11 - Contact List
 * Description: This program takes in names and phone numbers, stores them in a linked list, and prints them
 * Assume that three contacts are given with names on a line and numbers on the line next to it.
 * Author name: Andre Rivera, Tanisha Damle
 * Author email: andre.rivera@sjsu.edu; tanisha.damle@sjsu.edu
 * Last modified date: April 17, 2023
 * Creation date: April 14, 2023
 * References: 
 * - https://learn.zybooks.com/zybook/SJSUCS149SE149AndreopoulosSpring2023/chapter/8/section/10
 
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Struct Definition for a linked list node
typedef struct ContactNode_struct{
   struct ContactNode_struct* nextNodePtr; // pointer to next node
   char* contactName; // name of contact
   char* contactPhoneNumber; // phone number of contact
} ContactNode;

// Function that takes in a given node pointer, initializes it, and assigns values.
void InitializeContactNode(ContactNode* node, char* name, char* phoneNumber)
{
   // memory allocation
   node->contactName = (char*)malloc(sizeof(char*)); 
   node->contactPhoneNumber = (char*)malloc(sizeof(char*));    
   
   // set values  
   strcpy(node->contactName, name);
   strcpy(node->contactPhoneNumber, phoneNumber);
   node->nextNodePtr = NULL;
}

// Function that returns the contact's name given a node pointer
char* GetName(ContactNode* node)
{
   return node->contactName;
}

// Function that returns the contact's phone number given a node pointer
char* GetPhoneNumber(ContactNode* node)
{
   return node->contactPhoneNumber;
}

// Function that returns the next node in the list given a node pointer
ContactNode* GetNext(ContactNode* node)
{
   return node->nextNodePtr;
}

// Function that inserts a node in the location after a given previous node.
void InsertAfter(ContactNode* previous, ContactNode* toInsert)
{
   //Example: 1 -> 2 | 3
   toInsert->nextNodePtr = previous->nextNodePtr;  // 1 -> 2 | 3 -> 2 
   previous->nextNodePtr = toInsert; // 1 -> 3 -> 2

}

// Function that prints the contents of a node, given a node pointer
void PrintContactNode(ContactNode* node)
{
   printf("Name: %s\n", node->contactName);
   printf("Phone number: %s\n", node->contactPhoneNumber);
}

// Main method that takes in three contacts using fgets, converts them into contact nodes, and then prints them out.
int main(void) {
   
   char* name = (char*)malloc(100);
   char* number = (char*)malloc(20);
   
   // Contact #1
   fgets(name, 100, stdin);
   fgets(number, 20, stdin);
   if (name[strlen(name) - 1] == '\n')
      name[strlen(name) - 1] = '\0'; /* replace newline with null */
   if (number[strlen(number) - 1] == '\n')
      number[strlen(number) - 1] = '\0'; /* replace newline with null */
      
   ContactNode* n1 = (ContactNode*)malloc(sizeof(ContactNode));
   InitializeContactNode(n1, name, number);
   printf("Person 1: %s, %s\n", GetName(n1), GetPhoneNumber(n1));
   
   // Contact #2
   fgets(name, 100, stdin);
   fgets(number, 20, stdin);
   if (name[strlen(name) - 1] == '\n')
      name[strlen(name) - 1] = '\0'; /* replace newline with null */      
   if (number[strlen(number) - 1] == '\n')
      number[strlen(number) - 1] = '\0'; /* replace newline with null */
      
   ContactNode* n2 = (ContactNode*)malloc(sizeof(ContactNode));
   InitializeContactNode(n2, name, number);
   printf("Person 2: %s, %s\n", GetName(n2), GetPhoneNumber(n2));
   InsertAfter(n1, n2);
   
   // Contact #3
   fgets(name, 100, stdin);
   fgets(number, 20, stdin);
   if (name[strlen(name) - 1] == '\n')
      name[strlen(name) - 1] = '\0'; /* replace newline with null */      
   if (number[strlen(number) - 1] == '\n')
      number[strlen(number) - 1] = '\0'; /* replace newline with null */
      
   ContactNode* n3 = (ContactNode*)malloc(sizeof(ContactNode));
   InitializeContactNode(n3, name, number);
   printf("Person 3: %s, %s\n\n", GetName(n3), GetPhoneNumber(n3));
   InsertAfter(n2, n3);
   
   // Print contacts by traversing linked list
   printf("CONTACT LIST\n");
   ContactNode* temp = n1;
   while(temp != NULL)
   {
       PrintContactNode(temp);
       printf("\n");
       temp = GetNext(temp);
   }
   
   
   return 0;
}

