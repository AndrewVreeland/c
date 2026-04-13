#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 12 
#define NUMTRAITS 7 
#define TOTAL 6     
#define BASECASESIZE 30 


const char TRAITS[NUMTRAITS][MAXSIZE + 1] =
    {"Cuteness", "Fluffiness", "Agility",
     "Friendliness", "Intelligence",
     "Laziness", "Total"};

typedef struct Cat
{
    char *name;
    int scores[NUMTRAITS];
} Cat;

int partition(Cat **catList, int low, int high, int pivotIdx, int traitSortIdx);
void swap(Cat **p1, Cat **p2);
void insertionSort(Cat **catList, int numOfCats, int traitSortIdx );
void readInput(Cat **catList, int numOfCats);
int compareTo(Cat *ptrC1, Cat *ptrC2, int key);
void quickSort(Cat **list, int n, int key);
void quickSortRec(Cat **list, int low, int high, int key);

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
        quickSort(catList, numOfCats, traitSortIdx);
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

// read cat data from input
void readInput(Cat **catList, int numOfCats)
{
    for (int i = 0; i < numOfCats; i++)
    {
        // allocate memory for cat
        Cat *cat = malloc(sizeof(Cat));
        catList[i] = cat;

        // read cat name
        char catName[MAXSIZE];
        scanf("%s", catName);
        int strLen = strlen(catName) + 1;

        // copy name to struct
        cat->name = malloc(strLen);
        strcpy(cat->name, catName);
        
        // calculate and store total score
        int total = 0;
        for (int j = 0; j < TOTAL; j++)
        {
            scanf("%d", &cat->scores[j]);
            total += cat->scores[j];
        }
        cat->scores[TOTAL] = total;
    }
}

// wrapper for quick sort
void quickSort(Cat **catList, int numOfCats, int traitSortIdx)
{
    quickSortRec(catList, 0, numOfCats - 1, traitSortIdx);
}

// recursive quick sort function
void quickSortRec(Cat **catList, int low, int high, int traitSortIdx)
{
    // check if partition is valid
    if (low < high)
    {
        // pick random pivot index
        int random = rand() % (high - low + 1) + low;

        // partition array and get fixed index
        int fixedIdx = partition(catList, low, high, traitSortIdx, random);

        // sort left side
        quickSortRec(catList, low, fixedIdx - 1, traitSortIdx);

        // sort right side
        quickSortRec(catList, fixedIdx + 1, high, traitSortIdx);
    }
}

// partition array for quick sort
int partition(Cat **catList, int low, int high, int traitSortIdx, int random)
{
    // move random pivot to start
    swap(&catList[low], &catList[random]); 

    // set pivot index
    int pivot = low;
    low++;

    // loop until pointers cross
    while (low <= high) 
    {
        // move left pointer if score is higher or name is earlier
        while (low <= high &&
               (compareTo(catList[low], catList[pivot], traitSortIdx) < 0 ||
                (compareTo(catList[low], catList[pivot], traitSortIdx) == 0 && strcmp(catList[low]->name, catList[pivot]->name) < 0)))
        {
            low++;
        }
        
        // move right pointer if score is lower or name is later
        while (low <= high &&
               (compareTo(catList[high], catList[pivot], traitSortIdx) > 0 ||
                (compareTo(catList[high], catList[pivot], traitSortIdx) == 0 && strcmp(catList[high]->name, catList[pivot]->name) > 0)))
        {
            high--;
        }
        
        // swap if pointers get stuck
        if (low <= high)
        {
            swap(&catList[low], &catList[high]);
            low++;
            high--;
        }
    }

    // move pivot to final sorted position
    swap(&catList[pivot], &catList[high]);
    return high;
}

// swap two cat pointers
void swap(Cat **p1, Cat **p2)
{
    Cat *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// compare scores for descending sort
int compareTo(Cat *C1, Cat *C2, int traitSortIdx)
{
    // return negative one if first score is higher
    if (C1->scores[traitSortIdx] > C2->scores[traitSortIdx])
        return -1;
        
    // return one if first score is lower
    if (C1->scores[traitSortIdx] < C2->scores[traitSortIdx])
        return 1;
        
    // return zero for tie
    if (C1->scores[traitSortIdx] == C2->scores[traitSortIdx])
        return 0;
}

// sort small arrays using insertion sort
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