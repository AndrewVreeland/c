#include <stdio.h>

#define blue 1
#define red 2

void callbyValue(int bucket2);
void callbyReference(int *bucket2);
void fakeSwap(int c, int y);
void trueSwap(int*a, int*b);


int main()
{
    int x =1, y =2;
    fakeSwap (x,y);
    printf("x: %d y: %d\n", x,y);
    printf("---------------\n");

    trueSwap(&x, &y);
    printf("x: %d , y: %d", x,y);

    int bucket1 = blue;
    callbyValue(bucket1);
    printf("\n-------------- \n");
    printf("call by value: \nbucket1 = %d\n", bucket1);
    printf("-------------- \n");
    callbyReference(&bucket1);
    
    printf("reference by value: \nbucket1 = %d\n", bucket1);

    return 0;
}

void callbyValue(int bucket2)
{
    bucket2 = red;
}

void callbyReference(int *bucket2)
{
    *bucket2 = red;
}

void fakeSwap(int a, int b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void trueSwap(int*a, int*b)
{   
    int tmp = *a;
    *a = *b;
    *b = tmp;
}   

