#include <stdio.h>
/*
! static memory is located in the stack
! dynamic memory is located in the heap
*/

exampleOfAllocation()
{
    int x; //^ static in the stack
    int *p1; //^ static in the stack
    int *p2 = malloc(sizeof(int)); //^ p2 is static in the stack and malloc is dynamic in the heap
    p1 = &x; //^ p1 points at the address of x 
    *p1 = 20; //^ x = 20;
    p1 = p2; //^ p1 is now pointing at the dynamic memory that p2 is looking at
    *p2 = x + 5; //^ dynamic memory is now 25
    free(p1); //! can write free p1 because p1 is pointing at dynamic memory, can also use p2 but DO NOT USE BOTH.
}