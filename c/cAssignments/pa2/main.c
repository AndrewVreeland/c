/*
!! COP 3502C PA1
!! This program is written by: Andrew T Vreeland
 */
#include <stdio.h>   // For scanf
#include <string.h>  // For strlen and strcpy
#include <stdlib.h>  // For malloc
#include <stdbool.h> // for boolean

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
void permutationSetUp(int numOfCats, int numOfTeams, int numOfRivals, float *bestGroupScore, float *bestTeamScores);
void calculateScores(int *perm, int head, int numOfTeams, int numOfRivals, float *bestGroupScore, float *bestTeamScore);
void permuatate(int *perm, int *used, int head, int chair, int numOfTeams, int numOfRivals, float *bestGroupScore, float *bestTeamScore);
void setupTeams(int numOfCats, int numOfTeams);
int populateRivals(int numOfCats);
float averageBaseScoreCalculation(int *perm, int startIndex, int endIndex);
int countHighPerformersTraits(int *perm, int startIndex, int EndIndex);
int breedDifferenceValidation(int *perm, int startIndex, int endIndex);
int synergyBonusApplies(int *perm, int startIndex, int endIndex);
int rivalPenaltyApplies(int *perm, int startIndex, int endIndex, int numOfRivals);
void print(float bestPermScore, int numOfTeams, int catsPerTeam, float *bestTeamScores);
void freeCats(int numCats);
void freeExtras(float *bestTeamScores);
void freeTracker(int numOfTeams);


Rivals *rivals;
float bestPermScore;
int **tracker;
Cat *cats;

int main(void)
{

    int numOfTeams;
    scanf("%d", &numOfTeams); // populating num teams

    float bestGroupScore = -1.0;
    
    float *bestTeamScores = malloc(sizeof(float) * numOfTeams);

    int numCats = 0;
    scanf("%d", &numCats);          // poplating num cats int
    int catsPerTeam = numCats;
    numCats = numCats * numOfTeams; // missread the input so adjusting input value for code to work.

    initializeCats(numCats);         // creates cats
    setupTeams(numCats, numOfTeams); // initializes and fills tracker with base indicies
    int numOfRivals = populateRivals(numCats);
    permutationSetUp(numCats, numOfTeams, numOfRivals, &bestGroupScore, bestTeamScores);
    print(bestGroupScore, numOfTeams, catsPerTeam, bestTeamScores);
    freeCats(numCats);
    freeTracker(numOfTeams);
    freeExtras(bestTeamScores);
    


    return 0;
}

void setupTeams(int numOfCats, int numOfTeams)
{
    int catsPerTeam = numOfCats / numOfTeams;
    //TODO
    tracker = malloc(sizeof(*tracker) * numOfTeams);
    int counter = 0;
    for (int i = 0; i < numOfTeams; i++)
    {
        //TODO
        tracker[i] = malloc(sizeof(int) * catsPerTeam);
        for (int j = 0; j < catsPerTeam; j++)
        {
            tracker[i][j] = counter;
            counter++;
        }
    }
}

void permutationSetUp(int numOfCats, int numOfTeams, int numOfRivals, float *bestGroupScore, float *bestTeamScore)
{

    int *perm = calloc(sizeof(int), numOfCats);
    int *used = calloc(sizeof(int), numOfCats);
    // need to populate with teams.

    permuatate(perm, used, numOfCats, 0, numOfTeams, numOfRivals, bestGroupScore, bestTeamScore);
    free(perm);
    free(used);
}
void calculateScores(int *perm, int head, int numOfTeams, int numOfRivals, float *bestGroupScore, float *bestTeamScores)
{

    int catsPerTeam = head / numOfTeams;
    float currentGroupTotal = 0;
    float tempTeamScores[numOfTeams];
    int teamCounter = 0;

    for (int i = 0; i < head; i += catsPerTeam) // Moves team by team
    {
        float currentTeamTotal = 0;
        float teamBonus = 0;

        // base score
        float averageBaseScore = averageBaseScoreCalculation(perm, i, i + catsPerTeam) / catsPerTeam; // calculates base score
        currentTeamTotal += averageBaseScore;

        // bonuses
        teamBonus += countHighPerformersTraits(perm, i, i + catsPerTeam); // checks for highperfomance bonuses
        teamBonus += breedDifferenceValidation(perm, i, i + catsPerTeam); // checks for breed occurances may add or subtract score

        int synergyValidation = synergyBonusApplies(perm, i, i + catsPerTeam); // checks for team synergy
        if (synergyValidation == catsPerTeam)                                  // if each cat has synergy
        {
            teamBonus += 30;
        }

        // position bonuses
        for (int j = 0; j < catsPerTeam; j++)
        {
            int catIndex = perm[i + j]; // make sure to check each team

            teamBonus += cats[catIndex].baseScore * (POSITION_BONUS[j] / 100);
        }

        // rival penalties
        int rivalValidation = rivalPenaltyApplies(perm, i, i + catsPerTeam, numOfRivals); // how many occurances of rivals
        rivalValidation *= 25;                                                            // multiply this by the subtraction amount
        teamBonus -= rivalValidation;                                                     // ppply value

        currentTeamTotal += teamBonus;

        // saves team score and add to toal
        tempTeamScores[teamCounter] = currentTeamTotal;
        teamCounter++;
        currentGroupTotal += currentTeamTotal;
    }
    if (currentGroupTotal > *bestGroupScore)
    {
        *bestGroupScore = currentGroupTotal; // Update the score in main

        for (int j = 0; j < numOfTeams; j++)
        {
            bestTeamScores[j] = tempTeamScores[j]; // Store winning team scores
            for (int k = 0; k < catsPerTeam; k++)
            {
                // Store winning cat indices in tracker
                tracker[j][k] = perm[j * catsPerTeam + k];
            }
        }
    }
}

void permuatate(int *perm, int *used, int head, int chair, int numOfTeams, int numOfRivals, float *bestGroupScore, float *bestTeamScore)
{
    if (head == chair) // if cat is = to the spot return
    {
        calculateScores(perm, head, numOfTeams, numOfRivals, bestGroupScore, bestTeamScore); // does scoring
        return;
    }

    for (int i = 0; i < head; i++)
    {
        if (!used[i]) // if seat is not used
        {
            used[i] = 1;                                                                                     // use seat
            perm[chair] = i;                                                                                 // the seat is now filled with i
            permuatate(perm, used, head, chair + 1, numOfTeams, numOfRivals, bestGroupScore, bestTeamScore); // recursive call to check the next seat
            used[i] = 0;                                                                                     // unuse the seat
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
    scanf("%s", tempName);             // holds name in temp
    int strLen = strlen(tempName) + 1; // finds strlen for malloc
    
    cat.name = malloc(strLen);         // creates percise space for name
    strcpy(cat.name, tempName);        // assigns name to cat struct

    // CAT BREED
    char tempBreed[MAX_STR + 1];    // placeholder for breed
    scanf("%s", tempBreed);         // saves scanned value into temp
    strLen = strlen(tempBreed) + 1; // gets string len for malloc
    
    cat.breed = malloc(strLen);     // creates space
    strcpy(cat.breed, tempBreed);   // assigns breed to cat struct

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

int populateRivals(int numOfCats)
{

    int numOfRivals = 0;
    scanf("%d", &numOfRivals);
    rivals = malloc(sizeof(Rivals) * numOfRivals); // creating space for array of rivals

    char tempRivalName1[MAX_STR];
    char tempRivalName2[MAX_STR];

    for (int i = 0; i < numOfRivals; i++) // loops through and populates each rival
    {
        scanf("%s", tempRivalName1);
        scanf("%s", tempRivalName2);
        for (int j = 0; j < numOfCats; j++) // loops through cats to find a name match so the rivals may point at one another
        {
            if (strcmp(cats[j].name, tempRivalName1) == 0)
            {
                rivals[i].cat1 = &cats[j];
            }
            else if (strcmp(cats[j].name, tempRivalName2) == 0)
            {
                rivals[i].cat2 = &cats[j];
                        }
        }
    }
    return numOfRivals;
}

int countHighPerformersTraits(int *perm, int startIndex, int EndIndex)
{

    if (startIndex == EndIndex) // base case
    {
        return 0;
    }

    int currentScore = 0; // additive value

    for (int i = 0; i < MAX_SCORES; i++)
    {
        if (cats[perm[EndIndex - 1]].scores[i] >= 90) // if cats score greater or equal to 90 increment score
        {
            currentScore += 5;
        }
    }
    return currentScore + countHighPerformersTraits(perm, startIndex, EndIndex - 1); // returning currentscore plus recursive call
}
int synergyBonusApplies(int *perm, int startIndex, int endIndex)
{
    if (startIndex == endIndex) // base case
    {
        return 0;
    }

    int synergy = 0; // synergy tracker

    for (int i = 0; i < MAX_SCORES; i++)
    {
        if (cats[perm[endIndex - 1]].scores[i] >= 85) // checks for synergy
        {
            synergy += 1;
            break; // if we find one score in a cat break from this loop and increment synergy
        }
    }
    if (synergy == 0) // if no synergy found in first cat reutrn, short circuit
    {
        return 0;
    }
    return synergy + synergyBonusApplies(perm, startIndex, endIndex - 1); // will continue synergy search if first cat has synergy
}

float averageBaseScoreCalculation(int *perm, int startIndex, int endIndex)
{
    if (startIndex == endIndex) // base case
    {
        return 0;
    }

    float baseScore = 0;

    for (int i = 0; i < MAX_SCORES; i++)
    {
        baseScore += cats[perm[endIndex - 1]].scores[i]; // adding in base score for all score for the cat
    }

    return baseScore + averageBaseScoreCalculation(perm, startIndex, endIndex - 1); // recurrsive call to get score for next cat on team
}

int breedDifferenceValidation(int *perm, int startIndex, int endIndex)
{
    int score = 0;
    for (int i = startIndex; i < endIndex; i++) // looping through cats to compare breeds
    {
        for (int j = i + 1; j < endIndex; j++)
        {
            if (strcmp(cats[perm[i]].breed, cats[perm[j]].breed) == 0)
            {
                return score -= 15; // if match then subtract 15
            }
        }
    }
    return score += 10; // if no match then + 10 to score
}

int rivalPenaltyApplies(int *perm, int startIndex, int endIndex, int numOfRivals)
{
    if (startIndex == endIndex - 1) // bae case
    {
        return 0;
    }

    int count = 0; // occurances of rival pairs
    for (int k = 0; k < numOfRivals; k++)
    {
        if ((strcmp(rivals[k].cat1->name, cats[perm[startIndex]].name) == 0 && (strcmp(rivals[k].cat2->name, cats[perm[startIndex + 1]].name)) == 0)     // checks A and B
            || (strcmp(rivals[k].cat2->name, cats[perm[startIndex]].name) == 0 && (strcmp(rivals[k].cat1->name, cats[perm[startIndex + 1]].name)) == 0)) // checks B and A
        {
            count++; // increment count
        }
    }

    return count + rivalPenaltyApplies(perm, startIndex + 1, endIndex, numOfRivals); // returns count + next function call
}

void print(float bestPermScore, int numOfTeams, int catsPerTeam, float *bestTeamScores)
{
    printf("Best Teams Grouping score: %.2f\n", bestPermScore);

    int bestTeamIndex = 0;
    float maxTeamScore = -1.0;

    for (int i = 0; i < numOfTeams; i++)
    {
        printf("Team %d: ", i + 1);
        for (int j = 0; j < catsPerTeam; j++)
        {
            printf("%s ", cats[tracker[i][j]].name);
        }

        printf("%.2f\n", bestTeamScores[i]);

        // Track which team had the highest score for the "Best Candidate" line
        if (bestTeamScores[i] > maxTeamScore)
        {
            maxTeamScore = bestTeamScores[i];
            bestTeamIndex = i;
        }
    }

    // Print the names of the cats in the single best team
    printf("Best Candidate: ");
    for (int j = 0; j < catsPerTeam; j++)
    {
        printf("%s ", cats[tracker[bestTeamIndex][j]].name);
    }
    printf("\n");
}


// free functionality
void freeCats(int numCats)
{
    for (int i = 0; i < numCats; i++)
    {
        free(cats[i].name);
        free(cats[i].breed);
    }
    free(cats);

}

void freeExtras(float *bestTeamScores)
{
    free(bestTeamScores);
    free(rivals);
}

void freeTracker(int numOfTeams)
{
    for(int i =0; i < numOfTeams; i ++)
    {
        free(tracker[i]);
    }
    free(tracker);
}
