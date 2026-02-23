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
SLLNode **readInfo(int *arraySize, SLLNode **array, int *catCount);
void treat(Queue *queue);
void push(stack *stack, SLLNode *node);
void pop(stack *stack);
SLLNode *dequeue(Queue *queue);
void exposedCats(stack *stack);

SLLNode **readInfo(int *arraySize, SLLNode **array, int *catCount)
{

    int timeInput = 0;
    scanf("%d", &timeInput);

    int counter = 0; // tracks the amount of items for array inserts

    while (timeInput != -1)
    {
        // creating node and cat space
        SLLNode *node = malloc(sizeof(SLLNode));
        Cat *cat = malloc(sizeof(Cat));

        // initalizing node
        node->cat = cat;
        node->next = NULL;

        // filling cat name
        char tempName[25];
        scanf("%s", tempName);
        int strLen = strlen(tempName) + 1;
        char *name = malloc(strLen);
        strcpy(name, tempName);

        // filling cat duration
        int durration = 0;
        scanf("%d", &durration);

        // handling realloc
        if (counter == *arraySize)
        {
            int newSize = *arraySize * 2;
            SLLNode **newArr = realloc(array, sizeof(SLLNode *) * newSize);
            array = newArr;
            *arraySize = newSize;
        }
        // assinging node to array and incrementing counter
        if (durration > 0)
        {
            node->cat->arrival = timeInput;
            node->cat->name = name;
            node->cat->duration = durration;
            array[counter] = node;
            counter++;
        }
        // scans for next time input
        scanf("%d", &timeInput);
    }
    // reallocs the array to the appropriate size
    if (counter == *arraySize)
    {
        int newSize = (*arraySize) * 2;
        SLLNode **newArr = realloc(array, sizeof(SLLNode *) * newSize);
        array = newArr;
        *arraySize = newSize;
    }

    array[counter] = NULL; // setting each indicie to null
    *catCount = counter; // setting catCount for parent function
    return array; 
}

void prepareInfo(Queue *queue) // filter given array
{
    int arraySize = 10; // arbirtatry size

    SLLNode **array = malloc(sizeof(SLLNode *) * arraySize); // array to filter by time
    int catCount = 0;

    array = readInfo(&arraySize, array, &catCount); // populates array with unfiltered cats

    SLLNode *currentNode;
    currentNode = queue->head;

    int catsRemaining = catCount;
    bool canUse = true;

    while (catsRemaining > 0)
    {
        int current = -1; // reset the current array indicie

        for (int i = 0; i < catCount; i++)
        {
            // reset check variables
            canUse = true;
            currentNode = queue->head;

            // filters cats for duplicates
            while (currentNode)
            {
                if (array[i]->cat == currentNode->cat)
                {
                    canUse = false;
                    break; // Found him, no need to keep looking in the queue
                }
                currentNode = currentNode->next;
            }

            if (canUse) // if cat is available is it the best one
            {
                // If we don't have a candidate yet, or this one arrives later than our current best
                if (current == -1 || array[i]->cat->arrival < array[current]->cat->arrival)
                {
                    current = i;
                }
            }
        }

        if (current != -1)
        {
            enqueue(queue, array[current]); // adds best cat
        }
        catsRemaining--; // deincrements cats 
    }
    free(array);
}
Queue *enqueue(Queue *queue, SLLNode *node)
{
    // saftey checks
    if (queue == NULL)
        return NULL;
    if (node == NULL)
    {
        return queue;
    }

    // if empty queue
    if (queue->head == NULL)
    {
        queue->head = node;
        queue->tail = node;
        return queue;
    }
    // all other cases
    queue->tail->next = node;
    queue->tail = node;
    queue->tail->next = NULL;
    return queue;
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

            if (currentTime >= queue->head->cat->arrival && // checks arrival time so cats are being seen as they arrive and dr is available.
                currentTime + queue->head->cat->duration <= dailyTimer) // makes sure we dont pass EOD 
            {

                currentUnoCat = dequeue(queue); 
                meetingTimerUno = currentUnoCat->cat->duration; // sets new meeting timer 
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
    printf("Exposed Cats\n"); // blanket print
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
