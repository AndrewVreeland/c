#include <stdio.h>
#include <stdlib.h>
int arr[] = {1, 2 , 3, 4, 5, 6, 7, 8 , 9 , 10};
int main()
{
    int midpoint;
    int arrLen = sizeof(arr) / sizeof(arr[0]);
    
    int right = arrLen -1;
    midpoint = arr[arrLen -1];
    int left = 0;

    int answer = 8;

    while(midpoint != answer)
    {
        if(midpoint == answer)
        {
            printf("I found the answer and it is : %d at position: %d\n", answer, arr[midpoint]);
            break;
        }
        if (arr[midpoint] > answer)
        {
            left = midpoint;
            midpoint = (left + right) / 2 ;
        }
        if(arr[midpoint] < answer)
        {
            right = midpoint;
            midpoint = (right + left)/ midpoint;
        }
        if(left == right)
        {
            printf("we did not find the answer sadly\n");
            break;
        }
    }

    return 0;
}