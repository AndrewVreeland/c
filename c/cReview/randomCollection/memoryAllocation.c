#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
*                 malloc, calloc functions
    • Malloc or calloc function can be used to dynamically allocate
    memory
*                • Malloc function prototype:
!   – void *malloc(size_t size);
    – It allocates unused space for an object
*    whose size in bytes is specified by size
!   – The value in the allocated space is unspecified in malloc. So, the space
!   contains garbage value
    – returns a pointer to the beginning of the memory allocated.
    – If the memory can’t be found, NULL is returned.
*          • An example line allocating memory for an int using malloc:
!   – int *p = (int *) malloc(sizeof(int));
    – This is happening in the above line:
    • Allocates 4 bytes of memory (as sizeof(int) is 4 bytes). The memory has
    garbage values
    • After allocating the memory, malloc returns the address (starting address)
    • It is casted to int pointer so that an int pointer can point to that address
    • Here (int *) line is converting/casting void pointer to int pointer
    • So, now you have a memory for an int!

*                 • Calloc:
!   – void *calloc(size_t nelem, size_t elsize);
    – It allocates an array of size nelem with each element of size elsize
    – returns a pointer to the beginning of the memory allocated.
!   – The spaces shall be initialized to all bits 0
    – If the memory can’t be found, NULL is returned.
*       • An example line allocating memory for an int using calloc:
!   – int *p = (int *) calloc(1, sizeof(int));
*   – This is happening in the above line:
    • Allocates one 4 bytes of memory (as sizeof(int) is 4 bytes). The memory has 0 as the
    value in it
    • After allocating the memory, calloc returns the address (starting address)
    • It is casted to int pointer so that an int pointer can point to that address
    • Here (int *) line is converting/casting void pointer to int pointer
    • So, now you have a memory for an int!
• Basically in both function you have to say how many bytes to allocate
(how to specify is different).
• Then, if the function successfully finds the memory it returns the pointer
to the beginning of the block of the memory returned.
• If unsuccessful, NULL is returned.


*               Dynamically Allocated Arrays
    • Sometimes you don’t know how big an array you will need until-runtime.
    • You can dynamically allocate memory in those cases.
!    int *ptr1 = (int*) malloc(10*sizeof (int));
*   • Remember that malloc and calloc return void pointers (void*). So, if you
*    want to use the allocated memory as an array, you must cast the array to
*    the type you want.
    • When you cast it, it knows know what type of array is it.
    • In some modern compiler, you can avoid casting. In that case it performs
    the casting automatically based on the type of pointer you are using.
    • The above line could be written in multiple lines:
!   int *ptr1;
!   ptr1 = (int*) malloc(10*sizeof (int));
    Now ptr1 can be treated as an array and you can iterate through it!
    -What values are stored in the array?
!   • ptr1 = (int*) calloc(10, sizeof (int));
    • How about the values of the ptr1 now if you use calloc?


*/

void exampleMallocAndCalloc()
{
    typedef struct memoryAllocation
    {
        int *p1;
        int *pt2;
        int *pt3;
    } memoryAllocation;

    memoryAllocation *memoryAllocate = calloc(10, sizeof(memoryAllocate));

    int *ptr1 = (int *)malloc(10 * sizeof(int)); // why are we casting?
    int *ptr3 = malloc(10 * sizeof(int));        // this creates 10 items of size int all with garbage
    char *ptr4 = malloc(10 * sizeof(char));
    char *ptr5 = malloc(10 * sizeof(char));
    int *ptr6 = malloc(10 * sizeof(int));
    int *ptr8 = calloc(10, sizeof(int));
    int *ptr9 = calloc(10, sizeof(int));
    int *ptr10 = calloc(10, sizeof(int));
    int *ptr2;
    int i;
    if (ptr1 == NULL)
    {
        printf("could not allocate memory\n");
        exit(-1);
    }
    else
    {
        printf("Memory allocated. Printing data: \n");
        printf("%d", ptr1[i]);
        //! will print garbage values
    }

    ptr2 = (int *)calloc(10, sizeof(int));
    if (ptr2 == NULL)
    {
        printf("could not allocate memory\n");
        exit(-1);
    }
    else
    {
        printf("Memory allocated. Printing data after calloc: \n");
        for (i = 0; i < 10; i++)
        {
            printf("%d", ptr2[i]);
            //! will print 0 for all elements
        }
    }

    int x;
    int *p1;
    int *p2 = calloc(10, sizeof(int));
    p1 = &x;
    *p1 = 20;
    p1 = p2;
    *p2 = x + 5;
    free(p2);
    *p1 = 100; // ! SEGMENTATION FAULT

    free(ptr1); //! must free memory here
    free(ptr2);
}

/*

*                               realloc
    • There might be cases when the allocated array size is not enough
    and you will need to resize the array.
    • How would you approach this?
!   • Naïve approach would be:
    – Allocate new memory
    – Copy the old data to the new allocated array
    – Free the old array.
    • We can avoid extra work through realloc function.
!   • void *realloc(void *ptr, size_t size);
*   • So here, ptr is the old pointer, and size is the new size.
    • It will allocate size amount of bytes and copy the content from the
    allocated data in ptr and return void pointer.
    • Let’s say values is an integer pointer and already allocated to
    numVals size. The following line will reallocate.
!   • values = (int*)realloc(values,(numVals+EXTRA)*sizeof(int));

*/

#define EXTRA 10

void exampleOfRealloc()
{
    int numVals;
    srand(time(0));
    printf("How many numbers? \n");
    scanf("%d", &numVals);
    int *values = malloc(numVals * sizeof(int));
    for (int i = 0; i < numVals; i++)
    {
        values[i] = rand() % 100;
    }

    for (int i = 0; i < numVals; i++)
    {
        printf("%d\n", values[i]);
    }
    values = realloc(values, (numVals + EXTRA) * sizeof(int));

    for (int i = 0; i < EXTRA; i++)
    {
        values[i + numVals] = rand() % 100;
    }
    numVals += EXTRA;

    for (int i = 0; i < numVals; i++)
    {
        printf("%d\n", values[i]);
    }
    free(values);
}

int *readArray(int size)
{
    int *p = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &p[i]);
    }
    return p;
}

int findmax(int arr[], int len)
{
    int max = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int* arrayFactory(int n);

int main()
{
    int size;
    int *myarr;
    printf("How many numbers? ");
    scanf("%d", &size);
    // // myarr = readArray(size);
    // printf("Printing the array from main function: ");
    // for (int i = 0; i < size; i++)
    //     printf("%d ", myarr[i]);
    // printf("\nThe max number in the array is %d", findmax(myarr, size));
    // free(myarr); // free the memory

    printf("enter size of arr\n");
    scanf("%d", &size);
    
    int* p = arrayFactory(size);

    for (int i = 0; i < size; i++)
    {
        printf("Arr location: %d and value: %d\n", i, p[i]);
    }
    free(p);
    return 0;
}

int* arrayFactory(int n)
{
   int* manager = calloc(n, sizeof(int));
   for(int i =0; i < n; i++)
   {
        manager[i] = rand()%10;
   }

   return manager;
}

//! values = realloc(values,(numVals+EXTRA)*sizeof(int));