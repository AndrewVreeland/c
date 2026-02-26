#include <stdio.h>
#include <stdlib.h>
int l1[] = {1, 2, 5, 7,  9, 10, 18};
int l2[] = {3, 7, 9, 10, 11, 12, 18};

//! if bsearch ( l2 , len2 , l1[i]) == 1) ---> M LOG M run time

void SLMPLinearRunTime(int l1[], int l2[], int s1, int s2)
{
    int i=0, j = 0;
    while(i < s1 && j < s2)
    {
        if(l1[i] < l2[j])
        {
            i++;
        }else if(l1[i] > l2[j])
        {
            j++;
        }
        else{
            printf("%d , ", l1[i]);
            i++;
            j++;
        }
    }
}
int main(void)
{
    SLMPLinearRunTime(l1, l2, 7,7);
    return 0;
}