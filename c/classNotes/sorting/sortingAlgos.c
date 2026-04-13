
/* C program for Merge Sort */
#include <stdlib.h>
#include <stdio.h>
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int left, int mid, int right)
{
    int sizeL = mid - left + 1;
    int sizeR = right - mid;

    int *L = malloc(sizeof(int) * sizeL);
    int *R = malloc(sizeR * sizeof(int));

    for (int i = 0; i < sizeL; i++)
    {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < sizeR; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < sizeL && j < sizeR)
    {
        if (L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = R[j];
            k++;
            j++;
        }
    }
    while (i < sizeL)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < sizeR)
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void quickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int k = partition(arr, left, right);
        quickSort(arr, left, k - 1);
        quickSort(arr, k + 1, right);
    }
}
int partition(int arr[], int left, int right)
{
    int random = left + rand() % (right - left + 1);
    swap(&arr[left], &arr[random]);
    int pivot = left;

    left++;

    while(left <= right)
    {
        while (left <= right && arr[left] < arr[pivot])
            left++;
    
        while(left <= right && arr[right] > arr[pivot]) right --;
    
        if(left <= right)
        {
            swap(&arr[left], &arr[right]);
        }
    }

    swap(&arr[pivot], &arr[right]);
    return right;

}

    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }
void mergeSort(int arr[], int l, int r)
{
    if (l > r)
    {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}
void bubbleSort(int arr[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        int isSwapped = 0;
        for(int j = 0; j< n-i; j++)
        {
            if(arr[j]> arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
                isSwapped = 1;
            }
        }
        if(!isSwapped) break;
    }
}

void insertionSort(int arr[], int n)
{
    for(int i = 1; i < n; i ++)
    {
        int j;
        int hand = arr[i];
        for(j = i-1; j >= 0; j-- )
        {
            if(arr[j] > hand)
            {
                arr[j+1] = arr[j];
            }
            else
                break;
        }
        arr[j+1] = hand;


    }
}
void selectionSort(int arr[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        int min_idx = i;
        for(int j = i+1; j < n; j ++)
        {
            if(arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&arr[i], &arr[min_idx]);
    }
}
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = 6;
    printf("Given array is \n");
    printArray(arr, arr_size);
    mergeSort(arr, 0, arr_size - 1);
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
