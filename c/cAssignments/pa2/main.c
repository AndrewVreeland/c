
#include <stdio.h>  // For scanf
#include <string.h> // For strlen and strcpy
#include <stdlib.h> // For malloc

#define MAX_SCORES 5 // size of a cat scores array representing 5 traits
#define MAX_STR 25   // maximum name length of a cat
const float POSITION_BONUS[10] = {3.0, 5.0, 4.0, 6.0, 7.0, 2.0, 8.0, 1.0, 9.0, 1.5};
// bonus percentages that apply to each positionCat *cats;

typedef struct Cat
{
    char *name;             // dynamically allocated cat name
    char *breed;            // dynamically allocated breed
    int scores[MAX_SCORES]; // array of size 5 representing trait scores
    int baseScore;          // sum of scores array
} Cat;

typedef struct Rivals
{
    Cat *cat1; // pointer to cat1
    Cat *cat2; // pointer to cat2

} Rivals;


Cat createCat();
void initializeCats();
void permutationSetUp(int numOfCats);
void print(int *perm, int head);
void permuatate(int *perm, int *used, int head, int chair);
void setupTeams(int numOfCats, int numOfTeams);
void populateRivals(int numOfCats);

Rivals *rivals;
float bestPermScore;
int **tracker;
Cat *cats;



int main(void)
{
    int numOfTeams;
    scanf("%d", &numOfTeams); // populating num teams

    int numCats = 0;
    scanf("%d", &numCats);              // poplating num cats int
    numCats = numCats * numOfTeams;

    initializeCats(numCats); // creates cats

    setupTeams(numCats, numOfTeams); // initializes and fills tracker with base indicies

    populateRivals(numCats);

    for(int i = 0; i < numCats; i++)
    {
        printf("%s", cats[i].name);
    }

    return 0;
}

void setupTeams(int numOfCats, int numOfTeams)
{
    int catsPerTeam = numOfCats / numOfTeams; 
    tracker = malloc(sizeof(*tracker) * numOfTeams);
    int counter = 0;
    for (int i = 0; i < numOfTeams; i ++)
    {
        tracker[i] = malloc(sizeof(int) * catsPerTeam);
        for(int j = 0; j < catsPerTeam; j++)
        {
            tracker[i][j] = counter;
            counter++;
            
        }
    }

    for(int i = 0; i < numOfTeams; i++)
    {
        for(int ij = 0; ij < catsPerTeam; ij++)
        {

            printf("%d ", tracker[i][ij]);
        }
        printf("\n");
    }

}

void permutationSetUp(int numOfCats)
{
    
    int* perm = calloc(sizeof(int), numOfCats);
    int* used = calloc(sizeof(int), numOfCats);


    permuatate(perm, used, numOfCats, 0);

}
void print(int *perm, int head)
{
    for(int i =0; i < head; i++)
    {
        printf("%d ", perm[i]);
    }
}

void permuatate(int *perm, int *used, int head, int chair)
{
    if(head == chair)
    {
        print(perm, head);
        return;
    }

    for(int i =0; i < head; i++)
    {
        if(!used[i])
        {
            used[i] = 1;
            perm[chair] = i;
            permuatate(perm, used, head, chair +1);
            used[i] = 0;
        }
    }
}

void initializeCats(int numCats)
{
    cats = malloc(sizeof(Cat) * numCats); // creates space for cat array
    for (int i = 0; i < numCats; i++)     // populates a cat at each indicie
    {
        cats[i] = createCat();
    }

}

Cat createCat()
{
    Cat cat;

    // CAT NAME
    char tempName[MAX_STR + 1];
    scanf("%s", tempName);                  // holds name in temp
    int strLen = strlen(tempName) + 1;      // finds strlen for malloc
    cat.name = malloc(strLen); // creates percise space for name
    strcpy(cat.name, tempName);              // assigns name to cat struct

    // CAT BREED
    char tempBreed[MAX_STR + 1];             // placeholder for breed
    scanf("%s", tempBreed);                 // saves scanned value into temp
    strLen = strlen(tempBreed) + 1;          // gets string len for malloc
    cat.breed = malloc(strLen); // creates space
    strcpy(cat.breed, tempBreed);             // assigns breed to cat struct

    // SCORE
    int totalScore = 0;
    for (int i = 0; i < 5; i++) // loop to assign trait scores to the array and calcs total
    {
        int value = 0;
        scanf("%d", &value);
        totalScore += value;
        cat.scores[i] = value;
    }
    cat.baseScore = totalScore;

    return cat;
}

void populateRivals(int numOfCats)
{

        int numOfRivals = 0;
    scanf("%d", &numOfRivals);
    printf(" num of rivals --- %d ---\n", numOfRivals);
    rivals = malloc(sizeof(rivals) * numOfRivals); // creating space for array of rivals

    char tempRivalName1[MAX_STR];
    char tempRivalName2[MAX_STR];


    for(int i = 0; i < numOfRivals; i++) // loops through and populates each rival
    {
        scanf("%s", tempRivalName1);
        scanf("%s", tempRivalName2);
        for(int j = 0; j < numOfCats; j++)
        {
            if(strcmp(cats[j].name, tempRivalName1) == 0)
            {
                rivals[i].cat1 = &cats[j];
                printf("rival 1 : %s ",   rivals[i].cat1->name);
            }
            else if(strcmp(cats[j].name, tempRivalName2) == 0)
            {
                rivals[i].cat2 = &cats[j];
                printf("rival 2 : %s ",   rivals[i].cat2-> name);

            }
            printf("\n ");
        }
    }
}

// int countHighPerformersTraits(int *perm, int catsPerTeam, int numOfCats)
// {
//     if(numOfCats == 0)
//     {
//         return;
//     }


//     int score = 0;

//     for (int i = 0; i < numOfCats; i += catsPerTeam)
//     {
//         for (int j = i; j < (i + catsPerTeam); j++)
//         {
//             int catIndicie = perm[j];
//             for (int k = 0; k < MAX_SCORES; k++)
//             {
//                 if (cats[catIndicie].scores[k] >= 90)
//                 {
//                     score += 5;
//                 }
//             }
//         }
//     }

//     return score;
// }

//     synergyBonusApplies(...)

//         rivalPenaltyApplies(...)