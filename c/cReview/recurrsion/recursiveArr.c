#include <stdio.h>
#include <stdlib.h> 

int data[] = {5, 10, 30, 52, 76, 43};

int recurrsiveArr(int data[], int i)
{
    if(i == 0)
    {
        return 0;
    }

    int returnVal =  data[i-1] ;
    printf("%d", data[i-1]);

    return returnVal + recurrsiveArr(data, i-1);



}