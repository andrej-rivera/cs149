#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ContactNode_struct{
   /* Define ContactNode struct here. */
   struct ContactNode_struct* nextNodePtr;
   char* contactName;
   char* contactPhoneNumber;
} ContactNode;

/* Define the functions here. */
void InitializeContactNode(ContactNode* node, char* name, char* phoneNumber)
{
   node->contactName = (char*)malloc(sizeof(char*));
   node->contactPhoneNumber = (char*)malloc(sizeof(char*));      
   strcpy(node->contactName, name);
   strcpy(node->contactPhoneNumber, phoneNumber);
   node->nextNodePtr = NULL;
}

char* GetName(ContactNode* node)
{
   return node->contactName;
}
char* GetPhoneNumber(ContactNode* node)
{
   return node->contactPhoneNumber;
}

ContactNode* GetNext(ContactNode* node)
{
   return node->nextNodePtr;
}

void InsertAfter(ContactNode* previous, ContactNode* toInsert)
{
   //ContactNode* temp = previous->nextNodePtr;
   toInsert->nextNodePtr = previous->nextNodePtr;   
   previous->nextNodePtr = toInsert;

}

void PrintContactNode(ContactNode* node)
{
   printf("Name: %s\n", node->contactName);
   printf("Phone number: %s\n", node->contactPhoneNumber);
}
int main(void) {
   
   char* name = (char*)malloc(100);
   char* number = (char*)malloc(20);
   
   
   fgets(name, 100, stdin);
   fgets(number, 20, stdin);
   if (name[strlen(name) - 1] == '\n')
      name[strlen(name) - 1] = '\0'; /* replace newline with null */
   if (number[strlen(number) - 1] == '\n')
      number[strlen(number) - 1] = '\0'; /* replace newline with null */
      
   ContactNode* n1 = (ContactNode*)malloc(sizeof(ContactNode));
   InitializeContactNode(n1, name, number);
   printf("Person 1: %s, %s\n", GetName(n1), GetPhoneNumber(n1));
   
   
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

