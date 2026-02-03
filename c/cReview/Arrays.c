/*
!                   Arrays
An array is a collection of variables, with:
*   • 1) The items are stored in consecutive memory locations
*   • 2) All the variables in an array are of the same type.
    • We define an array as follows: 
!    int data[10];
    • Here the size of the array is 10.
    • To index a particular variable/element of the array do asfollows:
!    data[4] = 120;
    • The first index is data[0] and last index is data[9]
    • The items are: data[0], data[1], data[2], …., data[9]
    • They contains garbage data if not initialized.
    • Another way of declaring and initializing array:
!   int data[] = {87, 99, 75, 88, 93, 56, 77, 84, 89, 79};

!              Pointers and Arrays
*   • Array elements are stored in consecutive memory locations
    • So, if you know the first address of the array, you can easily
    access the remaining array elements!
    • See the following example array.
!   • int A[8]
*    Index   A[0] A[1] A[2] A[3] A[4] A[5] A[6] A[7]
*    Value     5    6    8    23   22   9    90   4
*    address 1000 1004  1008 1012 1016 1020 1024 1028
*/
int main()
{   
    int size = 10, i = 0, j = 0;
    int array[size];
    int* pPtr = array + i; //let’s say i is an index of the array
    int* qPtr = array + j; //let’s say j is an index of the array
    return 0;
    
}

/* 
* The name array is equivalent to &array[0]
▪ It means, name of an array is a pointer
▪ pPtr++ increments pPtr to point to the next element
of array.
▪ pPtr += n increments pPtr to point to n elements
beyond where it currently points.
▪ pPtr-qPtr equals i-j.
▪ Thus, we can see that a pointer arithmetic depends
on the type.
▪ The increment or decrement will jump to 4 bytes if
the pointer is integer pointer.
*/

/*

!    array[0] is equivalent to *array
!    array[n] is equivalent to *(array + n)
▪ We know array name is equivalent to the address of
first element
▪ So, array is same as &array[0]
▪ So, *array is dereferencing and getting array[0]

*/

