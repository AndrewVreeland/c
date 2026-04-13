#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 12  // MAXSIZE is the maximum size of all strings in the problem, including both cat names and trait names.
#define NUMTRAITS 7 // NUMTRAITS is the total number of possible keys for sorting (six traits plus one for the total score).
#define TOTAL 6     // TOTAL is the index into the scores array indicating the total score for a cat.
#define BASECASESIZE 30
/*
BASECASESIZE is the size at which the recursive sorting algorithm must switch to
insertion sort. Although Insertion sort is 𝑂(𝑛2), it is a very good choice for small arrays.
*/
const char TRAITS[NUMTRAITS][MAXSIZE + 1] =
    {"Cuteness", "Fluffiness", "Agility",
     "Friendliness", "Intelligence",
     "Laziness", "Total"};

typedef struct Cat
{
    char *name;
    int scores[NUMTRAITS];
} Cat;

void insertionSort(Cat **catList, int numOfCats, int traitSortIdx);
void mergeSortRec(Cat **catList, int low, int high, int traitSortIdx);
void merge(Cat **catList, int low, int mid, int high, int traitSortIdx);
void readInput(Cat **catList, int numOfCats);

// Merge Sorts the array list of size n according to the trait
// indicated by the integer key.
void mergeSort(Cat **catList, int high, int traitSortIdx);

// Performs a Merge Sort on list[low..high] according to the trait
// indicated by the integer key
// Returns a negative integer if the cat pointed to by ptrC1
// "comes before" the cat pointed to by ptrC2 on the ranklist
// sorted by the trait indicated by the integer key, breaking ties
// by the cat's name in alphabetical order. Returns 0 if the
// two cats are identical and returns a positive integer if the
// cat pointed to by ptrC2 comes before the cat pointed to by ptrC1.

int compareTo(Cat *ptrC1, Cat *ptrC2, int key);

int main(void)
{
    int numOfCats;
    scanf("%d", &numOfCats);
    Cat **catList = malloc(sizeof(Cat *) * numOfCats); // allocates memory for cat list
    readInput(catList, numOfCats);                     // reads input doc and populates data

    // wrapper for quicksort
    int traitSortIdx;
    scanf("%d", &traitSortIdx);
    if (numOfCats <= 30)
    {
        insertionSort(catList, numOfCats, traitSortIdx);
    }
    else
    {
        mergeSort(catList, numOfCats - 1, traitSortIdx);
    }

    int counter = 1; // for print
    // print statement
    printf("%s Ranklist\n", TRAITS[traitSortIdx]);
    for (int i = 0; i < numOfCats; i++)
    {
        printf("%d. %-15s %d\n", counter, catList[i]->name, catList[i]->scores[traitSortIdx]);
        counter++;
    }

    // freeing
    for (int i = 0; i < numOfCats; i++)
    {
        free(catList[i]->name);
        free(catList[i]);
    }
    free(catList);
    return 0;
}

void mergeSort(Cat **catList, int high, int traitSortIdx)
{

    mergeSortRec(catList, 0, high, traitSortIdx);
}

void mergeSortRec(Cat **catList, int low, int high, int traitSortIdx)
{
    // check if array has more than one item
    if (low < high)
    {
        // find the middle index
        int mid = (low + high) / 2;
        
        // sort the left half
        mergeSortRec(catList, low, mid, traitSortIdx);
        
        // sort the right half
        mergeSortRec(catList, mid + 1, high, traitSortIdx);
        
        // combine both sorted halves
        merge(catList, low, mid, high, traitSortIdx);
    }
}

void merge(Cat **catList, int low, int mid, int high, int traitSortIdx)
{
    // get sizes of both halves
    int sizeL = mid - low + 1;
    int sizeR = high - mid;

    // allocate memory for temp arrays
    Cat **L = malloc(sizeof(Cat*) * sizeL);
    Cat **R = malloc(sizeR * sizeof(Cat*));

    // copy data to left array
    for (int i = 0; i < sizeL; i++)
    {
        L[i] = catList[low + i];
    }

    // copy data to right array
    for (int j = 0; j < sizeR; j++)
    {
        R[j] = catList[mid + 1 + j];
    }

    // starting indexes for merging
    int i = 0;
    int j = 0;
    int k = low;

    // compare and merge both arrays
    while (i < sizeL && j < sizeR)
    {
        // get score comparison
        int cmp = compareTo(L[i], R[j], traitSortIdx);
        
        // pick left cat if score is higher or name comes first
        if (cmp < 0 || (cmp == 0 && strcmp(L[i]->name, R[j]->name) < 0))
        {
            catList[k] = L[i];
            i++;
            k++;
        }
        else
        {
            // otherwise pick right cat
            catList[k] = R[j];
            k++;
            j++;
        }
    }
    
    // copy leftovers from left
    while (i < sizeL)
    {
        catList[k] = L[i];
        i++;
        k++;
    }
    
    // copy leftovers from right
    while (j < sizeR)
    {
        catList[k] = R[j];
        k++;
        j++;
    }
    
    // free temp memory
    free(L);
    free(R);
}

void readInput(Cat **catList, int numOfCats)
{
    for (int i = 0; i < numOfCats; i++)
    {

        Cat *cat = malloc(sizeof(Cat));
        catList[i] = cat;

        // naming logic, allocating proper space
        char catName[MAXSIZE];
        scanf("%s", catName);
        int strLen = strlen(catName) + 1;

        cat->name = malloc(strLen);
        strcpy(cat->name, catName);
        // logic for cat scores
        int total = 0;
        for (int j = 0; j < TOTAL; j++)
        {
            scanf("%d", &cat->scores[j]);
            total += cat->scores[j];
        }
        cat->scores[TOTAL] = total;
    }
}

// Compares the scores of two cats based on the selected trait.
// This function is specifically designed for a DESCENDING sort (Highest to Lowest).
int compareTo(Cat *C1, Cat *C2, int traitSortIdx)
{
    // If C1 has a higher score, return -1 to indicate it should come BEFORE C2
    if (C1->scores[traitSortIdx] > C2->scores[traitSortIdx])
        return -1;
    
    // If C1 has a lower score, return 1 to indicate it should come AFTER C2
    if (C1->scores[traitSortIdx] < C2->scores[traitSortIdx])
        return 1;
    
    // If the scores are exactly the same, return 0 to trigger the tie-breaker
    if (C1->scores[traitSortIdx] == C2->scores[traitSortIdx])
        return 0;
}

// sort small arrays
void insertionSort(Cat **catList, int numOfCats, int traitSortIdx)
{
    // start at second cat
    for (int i = 1; i < numOfCats; i++)
    {
        int j;
        // cat to be placed
        Cat *hand = catList[i]; 
        
        // check cats to the left
        for (j = i - 1; j >= 0; j--)
        {
            // get score comparison
            int cmp = compareTo(catList[j], hand, traitSortIdx);

            // shift if score is lower or name comes later
            if (cmp > 0 || (cmp == 0 && strcmp(catList[j]->name, hand->name) > 0))
            {
                // move left cat right
                catList[j + 1] = catList[j]; 
            }
            else
                // stop if in correct spot
                break; 
        }
        // place cat in empty slot
        catList[j + 1] = hand;
    }
}
