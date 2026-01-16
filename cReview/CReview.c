int x = 0;
int *p = &x; // here p is pointing to garbage
int *pointer1 = &x; // here pointer1 is declared and initalized to the value of x
// this may also be written as 
int *pointer1;
pointer1 = &x;

// printf("%d", *p); // this will print the value of x

int *p, q;
q = 1;
p = &q; // p is pointing at the address of q

// printf("%d", *p); // this will print q because we are printing the value that is stored to the address that p is pointing at. 

/*
- To declare a pointer add an * in front of its name
- To obtain the value of a variable pointed by a 
pointer, use * in front of a pointers name
*/

// !!!!!!!!!!!!!! AVOID SEGMENTATION FAULT !!!!!!!!!!!!!!!!!!!!

//* If a pointer is not initialized to any address, dereferencing that pointer
//* might result in garbage value, or can create segmentation fault/run-
//* time error *** as your code is trying to access a memory which is not
//* allocated to your program.

/* Assing to NULL 

int *aPtr = NULL;

***check if pointer is null to avoid runtime error***
if (aptr){SOME LOGIC}
*/ 



