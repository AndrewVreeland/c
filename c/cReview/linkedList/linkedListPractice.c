#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    struct node *next;
    int data;
} node;

node *insertNodesAfter4(node *head, int item)
{
    if (!head)
        return head;

    node *current = head -> next;

    if (head->data == 4)
    {
        node *newNode = malloc(sizeof(node));
        newNode->data = item;
        if (head->next)
        {
            newNode->next = head->next;
            head->next = newNode;

        }else
        {
            head -> next = newNode;
            newNode -> next = NULL;
        }
    }

    while (current)
    {
        if (current->data == 4)
        {
            node *tempNode = malloc(sizeof(node));
            tempNode -> data = item;
            tempNode ->next = current ->next;
            current -> next = tempNode;
            current = tempNode->next;
            
        }
        else{

            current = current -> next;
        }
    }
    return head;
}