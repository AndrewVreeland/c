#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

typedef struct CircularQueue
{
    int *items;
    int front;
    int capacity;
    int numOfElements;
} CircularQueue;

// Method Prototypes
void enqueue(struct CircularQueue *q, int value);
int dequeue(struct CircularQueue *q);
void display(struct CircularQueue *q);
bool isEmpty(struct CircularQueue *q);

int main()
{
    struct CircularQueue queue;
    queue.capacity = SIZE;                                     // Initialize capacity to 5
    queue.items = (int *)malloc(queue.capacity * sizeof(int)); // Initial allocation
    queue.front = -1;
    queue.numOfElements = 0;

    int choice, value;

    while (1)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Value: ");
            scanf("%d", &value);
            enqueue(&queue, value);
            break;
        case 2:
            value = dequeue(&queue);
            printf("Dequeued: %d\n", value);
            break;
        case 3:
            display(&queue);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid\n");
        }
    }
}

// --- YOU IMPLEMENT THE LOGIC BELOW ---

// void enqueue(struct CircularQueue *queue, int value)
// {
//     if (queue == NULL)
//         return;

//     // 1. If Full: Resize and Unwrap
//     if (queue->numOfElements == queue->capacity)
//     {
//         int oldCapacity = queue->capacity;
//         int newCapacity = oldCapacity * 2;
//         int *newArr = realloc(queue->items, sizeof(int) * newCapacity);

//         if (newArr == NULL)
//             return;

//         queue->items = newArr;
//         queue->capacity = newCapacity;

//         int i = 0;
//         while (i < queue->front)
//         {
//             queue->items[oldCapacity + i] = queue->items[i];
//             queue->items[i] = -1;
//             i++;
//         }
//     } // <-- THE RESIZE BLOCK ENDS HERE

//     // 2. If Empty: Initialize front
//     if (queue->front == -1)
//     {
//         queue->front = 0;
//     }

//     // 3. Standard Insertion
//     int insertIndex = (queue->front + queue->numOfElements) % queue->capacity;
//     queue->items[insertIndex] = value;
//     queue->numOfElements++;
// }

int dequeue(struct CircularQueue *queue)
{
    if (queue->numOfElements == 0)
        return -1;

    int returnVal = queue->items[queue->front];
    queue->front = (queue->front % queue->capacity) + 1;
    return returnVal;
}

void display(struct CircularQueue *queue)
{
    printf("front is : %d \n", queue->items[queue->front]);
    for (int i = 0; i < queue->numOfElements; i++)
    {
        int currentIndex = (queue->front + i) % queue->capacity;
        printf(" %d -> ", queue->items[currentIndex]);
    }
}

bool isEmpty(struct CircularQueue *queue)
{
    if (queue == NULL)
        return NULL;
    if (queue->numOfElements == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void enqueue(struct CircularQueue *queue, int value)
{
    if (queue == NULL)
        return;

    if (queue->capacity == queue->numOfElements)
    {
        int oldSize = queue->capacity;
        int newSize = queue->capacity * 2;
        int *newArr = realloc(queue->items, newSize * sizeof(int));
        if (newArr == NULL)
        {
            return; // failed realloc
        }

        newArr = queue->items;
        queue->items = newArr;
        for (int i = 0; i < queue->front; i++)
        {
            if (i < queue->front)
            {
                queue->items[i] = queue->items[oldSize + i];
                queue->items[i] = -1;
            }
        }
    }

    if (queue->front == -1)
    {
        queue->front = 0;
    }
    int indicie = (queue->front + queue->numOfElements) % queue->capacity;
    queue->items[indicie] = value;
    queue ->numOfElements ++;
}