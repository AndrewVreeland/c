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
    array[counter] = NULL;
    *catCount = counter;
    return array;
}

void prepareInfo(Queue *queue)
{
    int arraySize = 10; // arbirtatry size

    SLLNode **array = malloc(sizeof(SLLNode *) * arraySize); // array to filter by time
    int catCount = 0;

    array = readInfo(&arraySize, array, &catCount);

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
            enqueue(queue, array[current]);
        }
        catsRemaining--;
    }
}
Queue *enqueue(Queue *queue, SLLNode *node)
{
    if (queue == NULL)
        return NULL;
    if (node == NULL)
    {
        return queue;
    }

    if (queue->head == NULL)
    {
        queue->head = node;
        queue->tail = node;
        return queue;
    }

    queue->tail->next = node;
    queue->tail = node;
    queue->tail->next = NULL;
    return queue;
}

SLLNode *dequeue(Queue *queue)
{
    if (queue == NULL)
        return NULL;
    if (queue->head == NULL)
        return NULL;
    SLLNode *savedNode;
    savedNode = queue->head;
    if (queue->head->next == NULL)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
    {
        queue->head = queue->head->next;
    }

    return savedNode;
}

SLLNode *peek(Queue *queue)
{
    if (queue == NULL)
        return NULL;
    if (queue->head == NULL)
        return NULL;

    return queue->head;
}

// ! <arrival_time> <name> <duration>
void treat(Queue *queue)
{
    if (queue == NULL || queue->head == NULL)
    {
        printf("No Exposed Cats\n");
        return;
    }

    int dailyTimer = 480;
    int meetingTimerUno = 0;
    int meetingTimerDos = 0;
    int currentTime;
    char drUno[] = "Uno";
    char drDos[] = "Dos";

    SLLNode *currentUnoCat = NULL;
    SLLNode *currentDosCat = NULL;

    stack *stackDos = malloc(sizeof(stack));

    for (int i = 0; i < dailyTimer + 1; i++)
    {
        currentTime = i;

        if (meetingTimerUno > 0)
            meetingTimerUno--;
        if (meetingTimerDos > 0)
            meetingTimerDos--;

        if (meetingTimerUno == 0 && queue->head != NULL)
        {
            if (currentTime >= queue->head->cat->arrival &&
                currentTime + queue->head->cat->duration <= dailyTimer)
            {

                currentUnoCat = dequeue(queue);
                meetingTimerUno = currentUnoCat->cat->duration;
                printf("Doctor Uno treated %s at %d\n", currentUnoCat->cat->name, currentTime);
            }
        }
        if (meetingTimerDos == 0 && queue->head != NULL)
        {
            if (currentTime >= queue->head->cat->arrival &&
                currentTime + queue->head->cat->duration <= dailyTimer)
            {

                currentDosCat = dequeue(queue);
                meetingTimerDos = currentDosCat->cat->duration;
                push(stackDos, currentDosCat);
                printf("Doctor Dos treated %s at %d\n", currentDosCat->cat->name, currentTime);
            }
        }
    }
    while(queue ->head)
    {
        printf("Cannot accomodate %s\n", queue-> head->cat->name);
        queue-> head = queue->head -> next;
    }
    exposedCats(stackDos);

}
void exposedCats(stack *stack)
{
    if(stack == NULL) return;
    while(stack-> top)
    {
        printf("%s\n", stack->top->cat->name);
        pop(stack);
    }
}
void push(stack *stack, SLLNode *node)
{
    if (stack == NULL)
        return;

    if (stack->top == NULL)
    {
        stack->top = node;
        stack->top->next = NULL;
    }
    else
    {
        node->next = stack->top;
        stack->top = node;
    }
}
void pop(stack *stack)
{
    if (stack == NULL) return NULL;
    if (stack->top == NULL)return NULL;

    SLLNode *savedNode = stack -> top;
    stack -> top = stack -> top -> next;
    free (savedNode);
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

    return 0;
}
