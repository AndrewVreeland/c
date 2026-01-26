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

char **dictionary; // to store array of dynamically allocated strings for breeds types (e.g., {"Ragdoll","Siamese", "Maincoone"})
int breedCount;    // number of breed types

Kennel *createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary);

char **readBreeds(int *count)
{
    scanf("%d", count);                              // setting temp count for num of breeds
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
    /*

    !Preconditions:
        * count must be a valid memory address where the number of breeds
            can be stored
    !Postconditions:
        * returns a dynamically allocated array of strings loaded with the breed
            types from the input.
        * count is updated to reflect the number of breeds
    */
}
char *getCharPtrByBreed(char **dictionary, char *breedName, int breedCount)
{
    for (int i = 0; i < breedCount; i++)
    {
        if (strcmp(dictionary[i], breedName) == 0)
        {
            breedName = dictionary[i];
            return breedName;
        }
    }

    return NULL;

    /*

    !Preconditions
        * dictionary is a strings array storing the words representing possible breeds
        * breedName must be a non-null string representing the specific breed name to
            be found
        * breedCount is a valid int that represents the number of the breed names stored
            in the dictionary
    !Postconditions:
        * Returns a pointer to the matching string storing the breed if found, returns
            NULL if not found


    */
}
CatStore *createStore(int kennelCount, int breedCount, char **dictionary)
{
    CatStore *catStore = malloc(sizeof(CatStore));
    catStore->numKenels = kennelCount;

    int **capacityConstraints = malloc(sizeof(int *) * kennelCount);
    catStore->capacities = capacityConstraints;

    for (int i = 0; i < kennelCount; i++)
    {
        catStore->capacities[i] = malloc(sizeof(int) * breedCount);

        for (int j = 0; j < breedCount; j++)
        {
            scanf("%d", &capacityConstraints[i][j]);
        }
    }

    catStore->kennels = createKennels(capacityConstraints, kennelCount, breedCount, dictionary);

    return catStore;
    /*

    int **capacities; // dynamically allocated double int array stores the breeds constraints for all kennels
    int numKenels;    // specifies the total number of kennels this store owns
    Kennel *kennels;  // dynamically allocated array of kennels

    !Preconditions:
        * kennelsCount is a valid int representing the number of kennels this store has
        * breedCount is a valid int that represents the number of the breed names stored
            in the dictionary
        * dictionary is a strings array storing the words representing possible breeds
    !Postconditions:
        * returns a valid CatStore pointer that has been allocated for, and all fields were
            filled entirely with proper data from the input

    */
}

Kennel *createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary)
{
    Kennel *kennel = malloc(sizeof(Kennel) * kennelCount);

    for (int i = 0; i < kennelCount; i++)
    {
        char tempName[MAXLEN + 1];
        scanf("%s", tempName);
        int strLen = 0;
        strLen = strlen(tempName) + 1;
        kennel[i].location = malloc(sizeof(char) * strLen);
        strcpy(kennel[i].location, tempName);

        int numOfCats = 0;
        scanf("%d", &numOfCats);
        kennel[i].occupancy = numOfCats;
        kennel[i].cats = createCats(dictionary, breedCount, numOfCats);
        kennel[i].maxCapacity = 0;

        for (int j = 0; j < breedCount; j++)
        {
            kennel[i].maxCapacity += constraints[i][j];
        }
    }
    return kennel;

    /*

        char *location;  // dynamically allocated space for the location without wasting space
        int occupancy;   // stores the current number of cats in the kennel
        Cat **cats;      // dynamically allocated array of pointers to Cats that reside in the kennel
        int maxCapacity; // specifies the max cap to the kennel

    !     Preconditions:
    *       • constraints is a valid 2d int array that represent the breed limit for each kennel,
                with dimensions kennelCount rows and breedCount columns
    *       • kennelsCount is a valid int representing the number of kennels this store has
    *       • breedCount is a valid int that represents the number of the breed names stored
                in the dictionary
    *       • dictionary is a strings array storing the words representing possible breeds
    !   Postconditions:
    *       • Returns a dynamically allocated array of kennel structs of size kennelCount,
                with each field of every kennel struct properly filled

    */
}
Cat **createCats(char **dictionary, int breedCount, int count)
{
    Cat **cats = malloc(sizeof(*cats) * count); // creates cat pointers

    for (int i = 0; i < count; i++)
    {
        cats[i] = createSingleCat(dictionary, breedCount);
    }
    return cats;

    /*

    typedef struct Cat
    {
        char *name;   // dynamically allocated space for the name without wasting space
        int age;      // specifies the age of the cat
        float weight; // stores the decimal value in weight for this specific cat
        char *breed;  // points to an already allocated breed string (Ragdoll, Siamese, Maincoone, etc..). No malloc/calloc for this property
        int status;   // specifies if a cat is adopted, pending, or available, ranges from 0 to 2, initially set to available for newly added cats
    } Cat;

    !   Preconditions:
    *       • dictionary is a strings array storing the words representing possible breeds
    *       • breedCount is a valid int that represents the number of the breed names stored
                in the dictionary
    *       • count in a valid int representing the number of cats to create
    !   Postconditions:
    *       • Returns a dynamically allocated and properly filled array of Cat pointers of size
                count
    *       • Each pointer points to a new Cat with data properly stored in struct members

    */
}
Cat *createSingleCat(char **dictionary, int breedCount)
{

    Cat *cat = malloc(sizeof(Cat)); // creates individual cat at each indicie

    char tempName[MAXLEN + 1];
    int strLen = 0;
    scanf("%s", tempName);
    strLen = strlen(tempName) + 1;
    cat->name = malloc(sizeof(char) * strLen);
    strcpy(cat->name, tempName); // from 188 to 192 we are dynamically allocating cats name

    scanf("%d", &cat->age); // scanning in age and weight
    scanf("%f", &cat->weight);

    char tempBreed[MAXLEN + 1];
    scanf("%s", tempBreed);

    cat->breed = getCharPtrByBreed(dictionary, tempBreed, breedCount);

    cat->status = 2;
    return cat;

    /*

    !   Preconditions:
    *   • dictionary is a strings array storing the words representing possible breeds
    *   • breedCount is a valid int that represents the number of the breed names stored
            in the dictionary
    !   Postconditions:
    *   • Creates a single cat structure, reads in its data, initializes cat’s status to the
            integer representing ‘AVAILABLE’ as explained above, points to the
            corresponding breed from dictionary
    *   • Returns a pointer to the allocated Cat structure

    */
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
        return 0; // location not found

        /*

        !   Preconditions:
        *   • s is a properly allocated and filled CatStore pointer
        *   • location is a valid non null string representing the location of the kennel we are
                checking if we can move this cat to
        *   • breed is a valid string that represents the breed of the cat we want to move to
                the location
        *   • dictionary is a strings array storing the words representing possible breeds
        *   • breedCount is a valid int that represents the number of the breed names stored
                in the dictionary
        !   Postconditions:
        *   • Returns an integer representing if a cat of the given breed can be moved to the
                specific location.
        *   • If can be moved returns 1, if not, returns 0
        *   • A cat of a given breed can only be moved to the location if the location
                maximum capacity is not exceeded and the breed follows the capacity constraint
                this location has for this breed

        */
    }
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
    /*

    !   Preconditions:
    *   • s is a properly allocated and filled CatStore pointer
    *   • cat is a properly allocated and filled Cat pointer
    !   Postconditions:
    *   • Returns the pointer of the kennel holding this cat if found, otherwise, returns
            NULL

    */
}
int getCatPosi(Kennel *home, Cat *cat)
{

    /*

    !   Preconditions:
    *   • home is a valid Kennel pointer
    *   • cat is a properly allocated and filled Cat pointer
    !   Postconditions:
    *   • Returns an integer that represents what index the Cat is found at in the home
            kennel, if not found, returns -1

    */
}
Cat *getCatByName(CatStore *s, char *catName)
{

    /*

    !   Preconditions:
    *   • s is a properly allocated and filled CatStore pointer
    *   • catName is a valid non null string representing the cat name we’re looking for
    !   Postconditions:
    *   • searches the store and returns the pointer to the cat with the name catName

    */
}
void removeCatFromKennel(Kennel *k, Cat *cat)
{

    /*

!    Preconditions:
*   • k is a properly allocated and filled kennel pointer
*   • cat is a pointer of the cat to be removed from kennel k
!   Postconditions:
*   • cat is removed from kennel k, elements are shifted to fill in the gap, kennel’s
        size and cat array it adjusted
*   • cat is not to be freed in this function

    */
}
void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries)
{

    /*

    !   Preconditions:
    *   • s is a properly allocated and filled CatStore pointer
    *   • dictionary is a strings array storing the words representing possible breeds
    *   • breedCount is a valid int that represents the number of the breed names stored
            in the dictionary
    *   • numQueries is a valid int that represents the number of questions the function
            will handle
    !   Postconditions:
    *   • Handles each query accordingly (more details below), it is recommended that
            you write a separate function for each query and call them from this function

    */
}
void freeBreeds(char **dictionary, int breedCount)
{

    /*

    !   Preconditions:
    *   • dictionary is a strings array storing the words representing possible breeds
    *   • breedCount is a valid int that represents the number of the breed names stored
            in the dictionary
    !   Postconditions:
    *    All memory associated with dictionary is freed

    */
}
void freeStore(int count, CatStore *store)
{

    /*

    ! Preconditions:
    *   • count is an in integer that represents the number of kennels in the store
    *   • store is a properly allocated and filled CatStore pointer
    !   Postconditions:
    *   • All dynamically allocated memory within CatStore struct and its associated
            struct members is freed
    *   • Frees cats in every kennel first, then frees kennels, then frees the capacities and
            the store

    */
}
