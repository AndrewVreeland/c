#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

typedef struct node
{
    int data;
    struct node *next;
} node;
struct node *insert(struct node *list, int d);
struct node *del(struct node *list, int d);
void print(struct node *list);
void freeList(struct node *list);
void copy(struct node *q, struct node **s);
int main()
{

    int number = 0, choice = 0;
    struct node *pList = NULL;
    struct node *nList = NULL;
    // Let the user add values until they enter -1.
    while (choice != 4)
    {
        // Get the operation.
        printf("\nDo you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
        scanf("%d", &choice);
        printf("Your choice is %d\n", choice);
        // Execute the operation.
        if (choice == 1)
        {
            // Get the number.
            printf("Enter the value to insert\n");
            scanf("%d", &number);
            pList = insert(pList, number);
            // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            // printf("\n");
        }
        else if (choice == 2)
        {
            // Get the number.
            printf("Enter the value to delete.\n");
            scanf("%d", &number);
            pList = del(pList, number);
            // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            // printf("\n");
        }
        else if (choice == 3)
        {
            if (nList)
                freeList(nList);
            copy(pList, &nList); // passing reference of nList as it is not

            // Look at the list.
            printf("Items in NEW linked list: ");
            print(nList);
            // printf("\n");
        }
        else
        {
            break;
        }
    }
    freeList(nList);
    freeList(pList);
    printf("Bye..\n");
    return 0;
}
/* copies a linked list into another */
void copy(struct node *source, struct node **dest)
{
    if (source != NULL)
    {
        *dest = malloc(sizeof(node));
        (*dest)->data = source->data;
        (*dest)->next = NULL;
        copy(source->next, &((*dest)->next));
    }
}
node *copy2(node *source)
{
    if (source == NULL)
    {
        return NULL;
    }

    node *newNode = malloc(sizeof(node));
    newNode->data = source->data;
    newNode->next = copy2(source->next);
    return newNode;
}
// Recursively inserts item into the LL pointed to by list.
struct node *insert(struct node *list, int item)
{
    if (list == NULL || item <= list->data)
    {
        node *newNode = malloc(sizeof(node));
        newNode->data = item;
        newNode->next = list;
        return newNode;
    }
    list->next = insert(list->next, item);
    return list;
}
// Recursively deletes the first node storing item in the list pointed to
// by list. If no such node exists, no changes are made. a pointer to the front
// of the resulting list is returned.
struct node *del(struct node *list, int item)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (list->data == item)
    {
        node *rest = list->next;
        free(list);
        return rest;
    }
    list->next = del(list->next, item);
    return list;
}
void print(struct node *list)
{
    if (list == NULL)
    {
        return;
    }

    printf("->%d", list->data);
    print(list->next);
}
// Frees each node in the LL pointed to by list.
void freeList(struct node *list)
{
    if (list == NULL)
    {
        return;
    }

    freeList(list->next);
    free(list);
}