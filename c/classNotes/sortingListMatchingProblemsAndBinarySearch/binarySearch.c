#include <stdio.h>

int binarySearch(int arr[], int size, int target);
int recursiveBinarySearch(int arr[], int size, int target, int left, int right);

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrLen = sizeof(arr) / sizeof(arr[0]);

    int left = 0;
    int right = arrLen - 1;

    int answer = binarySearch(arr, arrLen, 12);
    printf("answer : %d", answer);

    return 0;
}

int recursiveBinarySearch(int arr[], int size, int target, int left, int right)
{
    if (target == (arr[(right + left) / 2]))
        return (left + right) / 2;
    if (left >= right)
        return -1;

    if (target > arr[(right + left) / 2])
    {
        left = (right + left) / 2 + 1;
    }

    if (target < arr[(right + left) / 2])
    {
        right = (right + left) / 2 - 1;
    }
    return recursiveBinarySearch(arr, size, target, left, right);
}

int binarySearch(int arr[], int size, int target)

{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int midpoint = left + (right - left) / 2;

        if (arr[midpoint] == target)
        {
            return midpoint; // Found it!
        }

        if (arr[midpoint] > target)
        {
            right = midpoint - 1;
        }
        else
        {
            left = midpoint + 1;
        }
    }

    return -1; // Not found
}

int recursiveBinarySearch2(int arr[], int size, int target, int left, int right)
{
    if (target == arr[(left + right) / 2])
        return (left + right) / 2;
    if (left >= right)
        return -1;

    if (target > arr[(left + right) / 2])
    {
        left = (left + right) / 2 + 1;
    }

    if (target < arr[(left + right) / 2])
    {
        right = (left + right) - 1;
    }

    return recursiveBinarySearch2(arr, size, target, left, right);
}