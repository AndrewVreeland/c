/*
!! COP 3502C PA1
!! This program is written by: Andrew T Vreeland
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 25

typedef struct Cat
{
    char *name;   // dynamically allocated space for the name without wasting space
    int age;      // specifies the age of the cat
    float weight; // stores the decimal value in weight for this specific cat
    char *breed;  // points to an already allocated breed string (Ragdoll, Siamese, Maincoone, etc..). No malloc/calloc for this property
    int status;   // specifies if a cat is adopted, pending, or available, ranges from 0 to 2, initially set to available for newly added cats
} Cat;

typedef struct Kennel
{
    char *location;  // dynamically allocated space for the location without wasting space
    int occupancy;   // stores the current number of cats in the kennel
    Cat **cats;      // dynamically allocated array of pointers to Cats that reside in the kennel
    int maxCapacity; // specifies the max cap to the kennel
} Kennel;

typedef struct CatStore
{
    int **capacities; // dynamically allocated double int array stores the breeds constraints for all kennels
    int numKenels;    // specifies the total number of kennels this store owns
    Kennel *kennels;  // dynamically allocated array of kennels
} CatStore;

const char STATUS_CAT[3][20] = {"ADOPTED", "PENDING", "AVAILABLE"};

Cat **createCats(char **dictionary, int breedCount, int count);
Cat *createSingleCat(char **dictionary, int breedCount);

char **dictionary; // to store array of dynamically allocated strings for breeds types (e.g., {"Ragdoll","Siamese", "Maincoone"})
int breedCount;    // number of breed types

Kennel *createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary);

char **readBreeds(int *count)
{
    scanf("%d", count);
    char **breeds = malloc(sizeof(char *) * *count); // char pointer points at array of breeds of tempcount length
    for (int i = 0; i < *count; i++)                 // loops through to access each pointer block where we will asign the breed types
    {
        char tempName[MAXLEN + 1];
        int strLen = 0;

        scanf("%s", tempName);                     // assigns value to tempname
        strLen = strlen(tempName) + 1;             // finds length of tempname for malloc size
        breeds[i] = malloc(sizeof(char) * strLen); // creates the proper size string at each array indicie
        strcpy(breeds[i], tempName);               // coppies tempname into the proper memory location
    }
    return breeds; // returns double pointer
}
char *getCharPtrByBreed(char **dictionary, char *breedName, int breedCount)
{
    // iterates through breed names
    for (int i = 0; i < breedCount; i++)
    {
        if (strcmp(dictionary[i], breedName) == 0) // checks if beed name macches that of current dict entry
        {
            breedName = dictionary[i]; // updates pointer to the dict string location
            return breedName;
        }
    }

    return NULL; // returns null if breed is not found
}
CatStore *createStore(int kennelCount, int breedCount, char **dictionary) // only method to be called in main out of the create methods
{
    CatStore *catStore = malloc(sizeof(CatStore)); // allocates memory for store
    catStore->numKenels = kennelCount;

    int **capacityConstraints = malloc(sizeof(int *) * kennelCount); // allocates array of int pointers
    catStore->capacities = capacityConstraints;

    for (int i = 0; i < kennelCount; i++) // loops through and fills specific breed limits
    {
        catStore->capacities[i] = malloc(sizeof(int) * breedCount);

        for (int j = 0; j < breedCount; j++)
        {
            scanf("%d", &capacityConstraints[i][j]); // reads each specific breed limit
        }
    }

    catStore->kennels = createKennels(capacityConstraints, kennelCount, breedCount, dictionary); // initializes kennels with constraints form above

    return catStore; // returns our store
}

Kennel *createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary)
{
    Kennel *kennel = malloc(sizeof(Kennel) * kennelCount); // initializes space for kennels based on kennel count

    for (int i = 0; i < kennelCount; i++) // loops through and allocates names of kennels locaitons and creates the appropriate amount of cats
    {
        char tempName[MAXLEN + 1]; // temp variable for name allocaiton
        scanf("%s", tempName);
        int strLen = 0;
        strLen = strlen(tempName) + 1;
        kennel[i].location = malloc(sizeof(char) * strLen); // allocates appropritate space based on string length
        strcpy(kennel[i].location, tempName);               // uses strcpy to apply the tempname to the allocated space

        int numOfCats = 0;
        scanf("%d", &numOfCats);
        kennel[i].occupancy = numOfCats; // sets occupancy value

        kennel[i].cats = createCats(dictionary, breedCount, numOfCats); // creates cats based on the vaules set above
        kennel[i].maxCapacity = 0;

        for (int j = 0; j < breedCount; j++)
        {
            kennel[i].maxCapacity += constraints[i][j]; // sets the max capacity based on the constraints of each breed
        }
    }
    return kennel; // returns a kennel pointer
}

Cat *createSingleCat(char **dictionary, int breedCount)
{

    Cat *cat = malloc(sizeof(Cat)); // creates individual cat at each indicie

    char tempName[MAXLEN + 1];
    int strLen = 0;
    scanf("%s", tempName);
    strLen = strlen(tempName) + 1;
    cat->name = malloc(sizeof(char) * strLen);
    strcpy(cat->name, tempName); // from 137 to 142 we are dynamically allocating cats name

    scanf("%d", &cat->age); // scanning in age and weight
    scanf("%f", &cat->weight);

    char tempBreed[MAXLEN + 1];
    scanf("%s", tempBreed); // scanning in breed

    cat->breed = getCharPtrByBreed(dictionary, tempBreed, breedCount); // assining the breed to the appropriate pointer

    cat->status = 2; // setting status to available
    return cat;
}

Cat **createCats(char **dictionary, int breedCount, int count)
{
    Cat **cats = malloc(sizeof(*cats) * count); // creates cat pointers

    for (int i = 0; i < count; i++)
    {
        cats[i] = createSingleCat(dictionary, breedCount); // creates single cat for each allocated space
    }
    return cats;
}

int canMoveTo(CatStore *s, char *location, char *breed, char **dictionary, int breedCount)
{
    // find index of breed in dict
    int breedIndx = -1;
    for (int i = 0; i < breedCount; i++)
    {
        if (strcmp(dictionary[i], breed) == 0)
        {
            breedIndx = i;
            break;
        }
    }
    // loop through kennels find locaiton
    for (int i = 0; i < s->numKenels; i++)
    {
        if (strcmp(s->kennels[i].location, location) == 0)
        {
            // is kennel at max xcopacity
            if (s->kennels[i].occupancy >= s->kennels[i].maxCapacity)
            {
                return 0; // No room at all
            }
            // check breed capacity constraint
            int currentBreedCount = 0;
            for (int j = 0; j < s->kennels[i].occupancy; j++)
            {
                if (strcmp(s->kennels[i].cats[j]->breed, breed) == 0)
                {
                    currentBreedCount++;
                }
            }
            // has the limit been hitfor this breed
            if (currentBreedCount < s->capacities[i][breedIndx])
            {
                return 1; // Room available for this breed!
            }
            else
            {
                return 0; // Breed limit reached
            }
        }
    }
    return 0; // location not found
}
Kennel *getKennelByCat(CatStore *s, Cat *cat)
{

    // Loop through each kennel in the store
    for (int i = 0; i < s->numKenels; i++)
    {
        //  Loop through the array of Cat pointers in the current kennel
        for (int j = 0; j < s->kennels[i].occupancy; j++)
        {
            //  Compare the memory addresses of the pointers
            if (s->kennels[i].cats[j] == cat)
            {
                // Return
                return &s->kennels[i];
            }
        }
    }

    // 4. If we exhaust all kennels and cats, the cat is not in this store
    return NULL;
}
int getCatPosi(Kennel *home, Cat *cat)
{
    for (int i = 0; i < home->occupancy; i++) // loop through pointers in the kennel
    {
        if (home->cats[i] == cat)
        {
            return i; // returns the index of the cat position
        }
    }
    return -1;
}
Cat *getCatByName(CatStore *s, char *catName)
{
    for (int i = 0; i < s->numKenels; i++) // looping through kenels
    {
        for (int j = 0; j < s->kennels[i].occupancy; j++) // looping through each kennel by their occupancy
        {
            if (strcmp(s->kennels[i].cats[j]->name, catName) == 0) // string compares the name at each index by the search
            {
                return s->kennels[i].cats[j]; // returns name if found
            }
        }
    }
    return NULL; // returns null if not
}
void removeCatFromKennel(Kennel *k, Cat *cat)
{
    int indx = getCatPosi(k, cat); // gets index value from previous method call

    if (indx != -1)
    {
        for (int i = indx; i < k->occupancy - 1; i++) // occupancy -1 to prevent overflow
        {
            k->cats[i] = k->cats[i + 1]; // moves cat from the right into the current slot
        }
        k->occupancy--; // updates occupancy to match current value
    }
}
void querie1(CatStore *s, char *breedType)
{
    int foundCatBreed = 0;
    for (int i = 0; i < s->numKenels; i++) // loops through each kennel
    {
        for (int j = 0; j < s->kennels[i].occupancy; j++) // loops though the cats at each kennel
        {
            if (strcmp(s->kennels[i].cats[j]->breed, breedType) == 0) // checks each cat's breed to the breed type
            {                                                         // if valid the function then prints the required values here
                 foundCatBreed = 1;
                printf("%s %.2f %d %s %s\n",
                       s->kennels[i].cats[j]->name,
                       s->kennels[i].cats[j]->weight,
                       s->kennels[i].cats[j]->age,
                       s->kennels[i].location,
                       STATUS_CAT[s->kennels[i].cats[j]->status]); // Coco 23.20 14 Auburndale AVAILABLE
            }
        }
    }
    if (foundCatBreed == 0)
    {
        printf("No cat with breed %s\n", breedType); // if unable to find breed then print
    }
}

void querie2(CatStore *s, char *catName, int newStatus)
{

    for (int i = 0; i < s->numKenels; i++) // loop through kennels in the store
    {
        Kennel *k = &s->kennels[i];
        for (int j = 0; j < s->kennels[i].occupancy; j++) // looping through each kennels cats to find the proper cat
        {
            if (strcmp(catName, s->kennels[i].cats[j]->name) == 0) // checking name match
            {
                Cat *targetCat = s->kennels[i].cats[j]; // keeps track of the cat memory address for freeing before realloc
                targetCat->status = newStatus;          // updates cat status

                printf("%s is now %s!\n", catName, STATUS_CAT[newStatus]); // prints updated status

                if (newStatus == 0) // IF STATUS IS ADOPTED
                {
                    removeCatFromKennel(k, targetCat);                                                         // removes the cat
                    s->kennels[i].cats = realloc(s->kennels[i].cats, s->kennels[i].occupancy * sizeof(Cat *)); // reallocates space since we are one cat short
                    free(targetCat->name);                                                                     // free the data from the prior cat name
                    free(targetCat);                                                                           // free the data from the the prior cat
                }

                return;
            }
        }
    }
}

void querie3(CatStore *s, char *location, char **dictionary, int breedCount, char *catName)
{
    Cat *tempCat;
    Cat *cat = getCatByName(s, catName);
    Kennel *Kennel = getKennelByCat(s, cat);

    if (canMoveTo(s, location, cat->breed, dictionary, breedCount) == 1) // verifies if move is possible
    {
        tempCat = cat; // temp pointer to handle the removal proccess

        removeCatFromKennel(Kennel, cat);      // removes cat
        for (int i = 0; i < s->numKenels; i++) // loops to find the the right kennel locaiton
        {
            if (strcmp(s->kennels[i].location, location) == 0) // if location matches then we assign cat and update occupancy
            {
                s->kennels[i].cats = realloc(s->kennels[i].cats, (s->kennels[i].occupancy + 1) * sizeof(Cat *)); // reallocs to hold the new cat
                s->kennels[i].cats[s->kennels[i].occupancy] = tempCat;
                s->kennels[i].occupancy++;
                printf("%s moved successfully to %s\n", catName, location);
                return;
            }
        }
    }
    else
    {
        printf("%s cannot take a %s cat!\n", location, cat->breed);
    }
}

void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries)
{
    for (int i = 0; i < numQueries; i++) // itterates through num queries
    {
        int queryType = 0;
        int statusChangeValue = 0;
        char breed[MAXLEN + 1];
        char catName[MAXLEN + 1];
        char location[MAXLEN + 1];

        scanf("%d", &queryType); // finds specific query

        switch (queryType) // takes query and runs appropriate function
        {
        case 1: // find all cats of breed type
            scanf("%s", breed);
            querie1(s, breed);
            break;
        case 2: // update cat status
            scanf("%d", &statusChangeValue);
            scanf("%s", catName);
            querie2(s, catName, statusChangeValue);
            break;
        case 3: // move cat to new location
            scanf("%s", catName);
            scanf("%s", location);
            querie3(s, location, dictionary, breedCount, catName);
            break;

        default:
            break;
        }
    }
}
void freeBreeds(char **dictionary, int breedCount)
{

    for (int i = 0; i < breedCount; i++) // loops through each breed name
    {
        free(dictionary[i]); // frees the breed names
    }
    free(dictionary); // frees the array of breed names
}
void freeStore(int count, CatStore *store)
{
    for (int i = 0; i < count; i++) // loops through each kennel
    {
        free(store->capacities[i]);                           // frees capacity constraints
        free(store->kennels[i].location);                     // frees location string
        for (int j = 0; j < store->kennels[i].occupancy; j++) // loops through each cat
        {
            free(store->kennels[i].cats[j]->name); // frees cat name
            free(store->kennels[i].cats[j]);       // frees cat struct
        }
        free(store->kennels[i].cats); // frees the cat array
    }
    free(store->kennels); // frees the kennel array

    free(store->capacities); // frees the capacity array
    free(store);             // frees the store
}
int main(void)
{
    int breedCount = 0;
    int kennelCount = 0;
    int querieCount = 0;
    CatStore *store;

    dictionary = readBreeds(&breedCount); // initalize global dict, everything else is depended on this method

    scanf("%d", &kennelCount);
    store = createStore(kennelCount, breedCount, dictionary); // this creates the store its kennels and all cats

    scanf("%d", &querieCount);
    runQueries(store, dictionary, breedCount, querieCount); // this runs the queries against our data

    freeStore(kennelCount, store); // frees all allocated memory
    freeBreeds(dictionary, breedCount);

    return 0;
}
