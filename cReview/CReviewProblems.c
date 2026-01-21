#include <stdio.h>
#include <string.h>


void Factorial(int* num, int amount)
{
    for (int i = 1; i <= amount; i++)
    {
        *num *= i;
    }
}

void power (int* num, int amount, int value)
{
    *num = 1;
    for(int i = 1; i <= amount; i++)
    {
        *num *= value;
    }
}

int isPrimeNumber(int num)
{
    for(int i = 2; i < num; i++ )
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}