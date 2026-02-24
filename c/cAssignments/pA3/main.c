/*
!! COP 3502C PA3
!! This program is written by: Andrew T Vreeland
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// ! <arrival_time> <name> <duration>
typedef struct Cat_s
{
    int arrival;  // Minutes since clinic opened (Unique)
    char *name;   // Unique cat name
    int duration; // Required treatment time in minutes
} Cat;
typedef struct SLLNode_s
{
    Cat *cat; // Pointer to a cat
    struct SLLNode_s *next;
} SLLNode;

typedef struct Queue
{
    SLLNode *head;
    SLLNode *tail;
} Queue;
typedef struct stack
{
    SLLNode *top;
} stack;

Queue *enqueue(Queue *queue, SLLNode *node);
void treat(Queue *queue);
void push(stack *stack, SLLNode *node);
void pop(stack *stack);
void insertToPlace(Queue *queue, SLLNode *node);
SLLNode *dequeue(Queue *queue);
void exposedCats(stack *stack);

void prepareInfo(Queue *queue)
{
    int timeInput;

    // Read first arrival time
    if (scanf("%d", &timeInput) != 1 || timeInput == -1)
    {
        return;
    }

    while (timeInput != -1)
    {
        // placeholders 
        char tempName[26];
        scanf("%s", tempName);

        int duration;
        scanf("%d", &duration);

        // only malloc if needed
        if (duration > 0)
        {
            SLLNode *node = malloc(sizeof(SLLNode));
            Cat *cat = malloc(sizeof(Cat));

            // nmae logic
            int strLen = strlen(tempName) + 1;
            char *name = malloc(sizeof(char) * strLen);
            strcpy(name, tempName);

            // Populate cat data
            cat->arrival = timeInput;
            cat->name = name;
            cat->duration = duration;
            node->cat = cat;
            node->next = NULL;

            // insertion logic
            enqueue(queue, node);
        }

        // Check for next entry
        if (scanf("%d", &timeInput) != 1)
            break;
    }
}
Queue *enqueue(Queue *queue, SLLNode *newNode) // insert to place logic Thanks for the catch on the sorting logic Adam
{ // saftey checks
    if (queue->head == NULL)
    {
        queue->head = newNode;
        queue->tail = newNode;
        newNode->next = NULL;
        return;
    }

    // cats arrival time is less than current head
    if (newNode->cat->arrival < queue->head->cat->arrival)
    {
        newNode->next = queue->head;
        queue->head = newNode;
        return;
    }

    // find proper point
    SLLNode *current = queue->head;
    while (current->next != NULL && current->next->cat->arrival < newNode->cat->arrival)
    {
        current = current->next;
    }

    // insert
    newNode->next = current->next;
    current->next = newNode;

    // update tail if last node
    if (newNode->next == NULL)
    {
        queue->tail = newNode;
    }
}

SLLNode *dequeue(Queue *queue)
{
    // saftey checks
    if (queue == NULL)
        return NULL;
    if (queue->head == NULL)
        return NULL;

    // saves node for return
    SLLNode *savedNode;
    savedNode = queue->head;
    // if only one node
    if (queue->head->next == NULL)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    // all others
    else
    {
        queue->head = queue->head->next;
    }

    return savedNode;
}

// ! <arrival_time> <name> <duration>
void treat(Queue *queue) // sort input
{
    if (queue == NULL || queue->head == NULL) // handles empty queue
    {
        printf("No Exposed Cats\n");
        return;
    }

    int dailyTimer = 480; // tracks daily work time
    // dr timers
    int meetingTimerUno = 0;
    int meetingTimerDos = 0;
    int currentTime;
    // dr names
    char drUno[] = "Uno";
    char drDos[] = "Dos";

    // tracks current best cat
    SLLNode *currentUnoCat = NULL;
    SLLNode *currentDosCat = NULL;

    // drdos stack
    stack *stackDos = malloc(sizeof(stack));
    stackDos->top = NULL; // saftey

    for (int i = 0; i < dailyTimer + 1; i++) // loops through the day
    {
        currentTime = i; // tracks current time

        // deincrements if above 0 to manage appointment durration
        if (meetingTimerUno > 0)
            meetingTimerUno--;
        if (meetingTimerDos > 0)
            meetingTimerDos--;

        if (meetingTimerUno == 0 && queue->head != NULL) // if the meeting time for uno and head exsists
        {

            if (currentTime >= queue->head->cat->arrival &&             // checks arrival time so cats are being seen as they arrive and dr is available.
                currentTime + queue->head->cat->duration <= dailyTimer) // makes sure we dont pass EOD
            {

                currentUnoCat = dequeue(queue);
                meetingTimerUno = currentUnoCat->cat->duration;                                 // sets new meeting timer
                printf("Doctor Uno treated %s at %d\n", currentUnoCat->cat->name, currentTime); // require print
                // clean up unused cat
                free(currentUnoCat->cat->name);
                free(currentUnoCat->cat);
                free(currentUnoCat);
                currentUnoCat = NULL; // safety check
            }
        }
        if (meetingTimerDos == 0 && queue->head != NULL) // same logic as abvove
        {
            if (currentTime >= queue->head->cat->arrival &&
                currentTime + queue->head->cat->duration <= dailyTimer)
            {

                currentDosCat = dequeue(queue);
                meetingTimerDos = currentDosCat->cat->duration;
                // instead of freeing we push to a stack
                push(stackDos, currentDosCat);
                printf("Doctor Dos treated %s at %d\n", currentDosCat->cat->name, currentTime);
            }
        }
    }
    while (queue->head) // loops through remeaining cats prints and frees
    {
        SLLNode *temp = dequeue(queue);
        printf("Cannot accommodate %s\n", temp->cat->name);
        free(temp->cat->name);
        free(temp->cat);
        free(temp);
    }
    exposedCats(stackDos); // passes the stack to proccess exposed cats
}
void exposedCats(stack *stack)
{
    // safety check
    if (stack == NULL)
        return;
    if (stack->top)
    {
        printf("Exposed Cats\n"); // blanket print
    }
    else if (!stack->top)
    {
        printf("No Exposed Cats\n");
    }
    while (stack->top) // prints the cats in the stack
    {
        printf("%s\n", stack->top->cat->name);
        pop(stack);
    }
    free(stack); // frees stack
}
void push(stack *stack, SLLNode *node)
{
    // saftey check
    if (stack == NULL)
        return;
    // handles only one node
    if (stack->top == NULL)
    {
        stack->top = node;
        stack->top->next = NULL;
    }
    // handles all other cases
    else
    {
        node->next = stack->top;
        stack->top = node;
    }
}
void pop(stack *stack)
{
    // saftey checks
    if (stack == NULL)
        return;
    if (stack->top == NULL)
        return;
    // tracks saved node as to push the stack on
    SLLNode *savedNode = stack->top;
    stack->top = stack->top->next;
    // frees saved node once proccessed
    free(savedNode->cat->name);
    free(savedNode->cat);
    free(savedNode);
}
int main()
{
    // initialize queue
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;

    // fills and filters into queue
    prepareInfo(queue);
    treat(queue);

    free(queue);
    return 0;
}
