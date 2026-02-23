#include <stdio.h>
#include <stdlib.h> 

typedef struct node
{
    node *next;
    int data;
}node;

int printAndAddLL(node *list, int data )
{
    if(list == NULL)
    {return NULL;}

    printf("%d", list -> data);
    int returnValue = 0;
    return returnValue + printAndAddLL(list-> next, data);
}