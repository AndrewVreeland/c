/* Lab 9 Skeleton Code
*
* Created by Adam Betinsky on 3/6/2025 to help save time in the lab
*
* Cleaned up by Adam Betinsky on 10/23/2025
*
* Insertion sort updated on 3/24/2026
*
* NOTE: This program will be slow for some of the algorithms! It's normal for
nothing to be outputted for minutes at a time when you hit run.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAXARRAYS 6
#define MAXVALUE 1000000


void randArray(int arr[], int size, int maxValue);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int l, int r);
void selectionSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void arrayCopy(int original[], int copy[], int size);
long timediff(clock_t t1, clock_t t2);
void swap(int *xp, int *yp);
int partition(int *vals, int low, int high);
void quickSort(int *numbers, int low, int high);
void mergeInsertionSort(int arr[], int l, int r);


int main()
{
    srand(time(0));

    int sizes[MAXARRAYS] = {10000, 20000, 30000, 40000, 50000, 100000};

    int *originalArray, *sortedArray;

    clock_t start, end;

    long elapsed;

    for(int i = 0; i < MAXARRAYS; i ++)

    {
        printf("current size %d \n", sizes[i] );

        originalArray = malloc(sizeof(int) * sizes[i]);
        sortedArray = malloc(sizeof(int) * sizes[i]);

        randArray(originalArray, sizes[i], MAXVALUE);

        arrayCopy(originalArray, sortedArray, sizes[i]);

        start = clock();
        bubbleSort(sortedArray, sizes[i]);

        end = clock();

        elapsed = timediff(start, end);

        printf("Sorting %d elemenets takes %ld miliseconds for BubbleSort\n", sizes[i], elapsed);


        arrayCopy(originalArray, sortedArray, sizes[i]);

        start = clock();
        selectionSort(sortedArray, sizes[i]);

        end = clock();

        elapsed = timediff(start, end);

        printf("Sorting %d elemenets takes %ld miliseconds for SelectionSort\n", sizes[i], elapsed);

        arrayCopy(originalArray, sortedArray, sizes[i]);

        start = clock();
        insertionSort(sortedArray, 0, sizes[i-1]);

        end = clock();

        elapsed = timediff(start, end);

        printf("Sorting %d elemenets takes %ld miliseconds for InsertionSort\n", sizes[i], elapsed);

        arrayCopy(originalArray, sortedArray, sizes[i]);

        start = clock();
        quickSort(sortedArray,0, sizes[i-1]);

        end = clock();

        elapsed = timediff(start, end);

        printf("Sorting %d elemenets takes %ld miliseconds for QuickSort\n", sizes[i], elapsed);


        arrayCopy(originalArray, sortedArray, sizes[i]);

        start = clock();
        mergeSort(sortedArray,0, sizes[i-1]);

        end = clock();

        elapsed = timediff(start, end);

        printf("Sorting %d elemenets takes %ld miliseconds for mergeSort\n", sizes[i], elapsed);

        arrayCopy(originalArray, sortedArray, sizes[i]);

        start = clock();
        mergeInsertionSort(sortedArray,0, sizes[i-1]);

        end = clock();

        elapsed = timediff(start, end);

        printf("Sorting %d elemenets takes %ld miliseconds for mergeInsertionSort\n", sizes[i], elapsed);

        free(originalArray);
        free(sortedArray);






    }

    return 0;
}

long timediff(clock_t t1, clock_t t2)
{
    // calculate the elapsed time of the passed clock_t variables using the formula
    // below and return the value
    long elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

void swap(int *xp, int *yp)
{
    // swap the passed integers using pass by reference
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int l, int r)
{
    int i, item, j;
    for (i = l + 1; i <= r; i++)
    {
        item = arr[i];
        for (j = i - 1; j >= l; j--)
        {
            if (arr[j] > item)
                arr[j + 1] = arr[j];
            else
                break;
        }
        arr[j + 1] = item;
    }
}

void mergeInsertionSort(int arr[], int l, int r)
{
    if(r -l + 1 <= 25)
    {
        insertionSort(arr, l , r);
        return;
    }

    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid +1, r);
        merge(arr, l, mid, r);
    }
    
}

void arrayCopy(int original[], int copy[], int size)
{
    for(int i = 0; i < size; i ++)
    {
        copy[i] = original[i];
    }
}

void randArray(int arr[], int size, int maxValue)
{
    for(int i = 0; i< size; i ++)
    {
        arr[i] = rand() % maxValue +1 ;
    }
}

void merge(int arr[], int l, int m, int r)
{
    int leftArrSize = m - l +1;
    int rightArrSize = r - m;

    int *leftHelperArr = malloc(leftArrSize * sizeof(int));
    int *rightHelperArr = malloc(rightArrSize * sizeof(int));

    int i, j, k;

    for(i = 0; i < leftArrSize; i ++)
    {
        leftHelperArr[i] = arr[l + i];
    }

    for(j < rightArrSize; j< rightArrSize; j++)
    {
        rightHelperArr[j] = arr[m +1 + j];
    }

    i = 0;
    j = 0;
    k =l;
    
    while(i < leftArrSize && j < rightArrSize)
    {
        if(leftHelperArr[i] < rightHelperArr[j])
        {
            arr[k] = leftHelperArr[i];
            i++;
        }
        else 
        {
            arr[k] = rightHelperArr[j];
            j++;
        }
        k ++;
    }

    while(i < leftArrSize)
    {
        arr[k] = leftHelperArr[i];
            i++;
            k++;
    }

    while(j < rightArrSize)
    {
        arr[k] = rightHelperArr[j];
            j++;
            k++;
    }
    free(leftHelperArr);
    free(rightHelperArr);


}

void mergeSort(int arr[], int l, int r) // breaks array in half into smaller sub arrays 
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid +1, r);
        merge(arr, l, mid, r);
    }
}

int partition(int *vals, int low, int high) // used in quicksort
{
    int pivot = low + rand() % (high - low +1);

    // swap low and pivot

    swap(&vals[low], &vals[pivot]);

    int originalLowPos = low;

    low++;

    while(low <= high)
    {
        while(low <= high && vals[low] <= vals[originalLowPos])
        {
            low++;
        }
        while(high >= low && vals[high] > vals[originalLowPos])
        {
            high --;
        }

        if(low < high)
        {
            swap(&vals[low], &vals[high]);
        }
    }

    swap(&vals[originalLowPos], &vals[high]);
    return high;

}

void quickSort(int *numbers, int low, int high)// nlogn but could be n^2 uses pivot
{
    if(low < high)
    {
        int split = partition(numbers, low, high); // finds the pivot point
        
        quickSort(numbers, split +1, high); // checks right sub array
        quickSort(numbers, low, split -1); // checks left sub array

    }


}

void selectionSort(int arr[], int n) // n^2 run time
{
    for(int i = 0; i < n-1; i ++ )
    {
        int minIndex = i;
        for(int j = 0; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(&arr[minIndex], &arr[i]);
    }
}
