#include <stdio.h>
#include <stdlib.h>
#include "main.h"
// this function takes an item and insert it in the linked list pointed by root.
node *insert_front(node *root, int item)
{
    node *temp;
    // create a new node and fill-up the node
    temp = (node *)malloc(sizeof(node));
    temp->data = item;
    temp->next = NULL;
    if (root == NULL) // if there is no node in the linked list
        root = temp;
    else // there is an existing linked list, so put existing root after temp
    {
        temp->next = root; // put the existing root after temp
        root = temp;       // make the temp as the root!
    }
    return root;
}
void display(node *t)
{
    printf("\nPrinting your linked list.......");
    while (t != NULL)
    {
        printf("%d ", t->data);
        t = t->next;
    }
}
node *reverse(node *head)
{   
    if (head == NULL || head ->next == NULL) return head;

    node *mainList = head->next;
    node *reversedList = head;
    node * walkerMain = mainList;
    node * walkerReverse = reversedList;

    reversedList ->next = NULL;

    while(mainList != NULL)
    {
        mainList = mainList -> next;
        walkerMain -> next = walkerReverse;
        walkerReverse = walkerMain;
        walkerMain = mainList;
    }
    reversedList = walkerReverse;
    return reversedList;

}
void insertToPlace(node *list, int val, int place)
{

    if(list == NULL || place <= 1)
    {
        printf("This is not a valid place \n");
        return;
    }

    node * newNode = malloc(sizeof(node));
    newNode -> data = val;
    newNode -> next = NULL;

    int counter = 1;

    while(list != NULL)
    {
        node *tempNode = list;
        list = list ->next; 
        counter ++;
        if(counter == place)
        {
            tempNode -> next = newNode;
            newNode -> next = list;
            break;
        }
        if (list -> next == NULL)
        {
            list ->next = newNode;
            break;
        }
    }

    //! more efficent approach from lab 
    // ? has less checks in the while loop
    /*
    while(list ->next != null && count < place -1)
    {
    list = list->next;
    count++;
    }
    newNode ->next = list ->next;
    list -> next = newNode; 
    */
}
int main()
{
    node *root = NULL; // very important line. Otherwise all function will fail
    node *t;
    int ch, ele, v, del;
    while (1)
    {
        printf("\nMenu: 1. insert at front, 2. reverse list 3. Insert to place0. exit: ");
        scanf("%d", &ch);
        if (ch == 0)
        {
            printf("\nGOOD BYE>>>>\n");
            break;
        }
        if (ch == 1)
        {
            printf("\nEnter data (an integer): ");
            scanf("%d", &ele);
            root = insert_front(root, ele);
            display(root);
        }
        if (ch == 2)
        {
            root = reverse(root);
            printf("List reversed.\n");
            display(root);
        }
        if (ch == 3)
        {
            int place;
            printf("\nEnter data (an integer) and place (>1) separated by space: ");
            scanf("%d %d", &ele, &place);
            insertToPlace(root, ele, place);
            display(root);
        }
    }
    return 0;
}
