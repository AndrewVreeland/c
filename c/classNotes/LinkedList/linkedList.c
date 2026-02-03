#include <stdio.h>>
#include <string.h>
#include <stdlib.h>

struct Book_node
{
    char name[20];
    char author[20];
    int year;
    struct  Book_node *next;
};

struct Book
{
    char name[20];
    char author[20];
    int year;
};

struct Book_node2
{
    struct Book;
    struct  Book_node2 *next;
};

void traverseLL()
{
    /*
    node *node;
    
    node = head; 
    
    while(node->Next != NULL)
    {
        printf("%d", node -> data);
        node = node ->Next;
    }

    !! Operations
    ^ general steps 
    1. create temp node
    2. look for position where to insert
    3. link the temp node appropreitley to the list
    */
}
