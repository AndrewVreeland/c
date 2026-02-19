#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

typedef struct CircularQueue
{
    int *items;
    int front;
    int rear;
    int capacity;
} CircularQueue;

// Method Prototypes
void enqueue(struct CircularQueue *q, int value);
int dequeue(struct CircularQueue *q);
void display(struct CircularQueue *q);
countElements(struct CircularQueue *queue);
bool isEmpty(struct CircularQueue *q);

int main()
{
    struct CircularQueue queue;
    queue.capacity = SIZE; // Initialize capacity to 5
    queue.items = (int*)malloc(queue.capacity * sizeof(int)); // Initial allocation
    queue.front = -1;
    queue.rear = -1;

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

void enqueue(struct CircularQueue *queue, int value)
{
    int numElements = countElements(queue);

    if (numElements == queue->capacity) 
    {
        int oldSize = queue->capacity;
        queue->capacity *= 2;
        
        queue->items = (int*)realloc(queue->items, queue->capacity * sizeof(int));

        // Only move things if we are currently wrapped
        if (queue->front > queue->rear) 
        {
            // Move everything from index 0 up to 'rear' 
            // to the new section starting at 'oldSize'
            for (int i = 0; i <= queue->rear; i++) 
            {
                queue->items[oldSize + i] = queue->items[i];
            }
            
            // Update the rear to its new location in the expanded space
            queue->rear = oldSize + queue->rear;
        }
    }

    // Standard insertion logic
    if (queue->front == -1) 
    {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->items[queue->rear] = value;
}

int dequeue(struct CircularQueue *queue)
{
    // Hint: Check isEmpty first, then update q->front
    return -1;
}

void display(struct CircularQueue *queue)
{
    // Hint: Use a loop from front to rear
}

int countElements(struct CircularQueue *queue)
{
    // If the queue is empty, count is 0
    if (queue->front == -1) 
    {
        return 0;
    }

    // Mathematical way to find the distance between two points in a circle
    return (queue->rear - queue->front + SIZE) % SIZE + 1;
}


bool isEmpty(struct CircularQueue *queue)
{
    if(queue == -1)
    {
        return true;
    }
    return false;
}