#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int fun(int n);
void decimalConversion(int n);

int main(void)
{
    int n = 5;
    int o = 105;
    printf("%d\n", fun(n));
    printf("\n!!!NEXT PROBLEM !!!\n");
    decimalConversion(o);


    
    return 0;
}

int fun(int n)
{
    if(n ==1)
        return 1;
    else 
    printf("%d, before return\n", n);
        return 1 + fun(n-1);
        printf("%d, after return\n", n);

}

int powRecurrsive(int base, int exp)
{
    if (exp == 0)
    return 1;

    return base * powRecurrsive(base, exp -1);
}

int sumArray(int arr[], int n)
{
    if(n <= 0)
    return 0;

    return arr[n-1] + sumArray(arr, n-1);
}

int palindrome(char word[], int start, int end)
{
    if(start >= end) return 1; // compares pointers if we get to this point then we have a PALINDROME

    if(word[start] == word[end-1])
    {
        return palindrome(word, start + 1, end -1); // recursive call
    }else 
    {
        return 0; // found mismatch
    }
}

void decimalConversion(int n)
{
    if(n == 0 ) return;

        decimalConversion(n/2);
        printf("%d", n%2);
}


int findTheMax(int arr[], int amountOfNumbersInArray)
{
    // Base Case: If there is only one element, it is the maximum.
    if (amountOfNumbersInArray == 1) 
    {
        return arr[0];
    }

    // Recursive Step: Get the maximum of the "rest" of the array.
    // We pass n - 1 to shrink the problem size.
    int maxOfRest = findTheMax(arr, amountOfNumbersInArray - 1);

    // Comparison: Compare the current last element (arr[n-1]) 
    // to the maximum we found in the rest of the array.
    if (arr[amountOfNumbersInArray - 1] > maxOfRest) 
    {
        return arr[amountOfNumbersInArray - 1];
    } 
    else 
    {
        return maxOfRest;
    }
}