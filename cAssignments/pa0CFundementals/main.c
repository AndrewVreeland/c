#include <stdio.h>
#include <string.h>
#include "main.h"

struct cat cats[MAXCATS];
int counter = 0; // number of cats
int max = MAXCATS;

struct KeyValuePair Letters[] = // this allows me to track the letter usage
    {
        {"A", 0, 0},
        {"B", 0, 0},
        {"C", 0, 0},
        {"D", 0, 0},
        {"E", 0, 0},
        {"F", 0, 0},
        {"G", 0, 0},
        {"H", 0, 0},
        {"I", 0, 0},
        {"J", 0, 0},
        {"K", 0, 0},
        {"L", 0, 0},
        {"M", 0, 0},
        {"N", 0, 0},
        {"O", 0, 0},
        {"P", 0, 0},
        {"Q", 0, 0},
        {"R", 0, 0},
        {"S", 0, 0},
        {"T", 0, 0},
        {"U", 0, 0},
        {"V", 0, 0},
        {"W", 0, 0},
        {"X", 0, 0},
        {"Y", 0, 0},
        {"Z", 0, 0},
};

int main()
{
    readData(cats, &max, &counter);
    int cutestCatIndex = getCutestCat(cats, counter); // saves the cutestCatIndex for use in the print function
    findLetterUsage(cats, &counter, Letters);
    printData(&counter, cutestCatIndex);
}

void readData(struct cat *cats, int *size, int *count)
{

    // this loops through the incoming cats based on the amount of them ( or size)
    for (int i = 0; i < *size; i++)
    {
        int holderValue = 0;    // holds ID while we preform data validation
        int lengthOfNumber = 0; // used to find the length of the id.

        // these scan and load the information into their respective cat structures1
        int status = scanf("%d", &holderValue); // returns -1 if EOF or not an int, 0 otherwise
        int temp = holderValue;                 // creates temp variable to enable us to manipulate data

        while (temp > 0) // while temp > 0 /10 to get number length
        {
            temp /= 10;
            lengthOfNumber += 1; // increment number length
        }
        while (lengthOfNumber != 6) // if a value is not 6 digits long we look until we find one or until EOF
        {
            lengthOfNumber = 0;
            int status = scanf("%d", &holderValue); // returns -1 if EOF or not an int, 0 otherwise
            int temp = holderValue;
            while (temp > 0) // same logic from up above
            {
                temp /= 10;
                lengthOfNumber += 1;
            }
            if (status == -1)
            {
                break;
            }
        }

        if (lengthOfNumber == 6)
        {
            cats[i].cat_ID = holderValue;
            if (status != -1)
            {
                (*count)++;                   // tracking how many cats we have
                scanf("%s", cats[i].catName); // scans cat name and then saves it under the appropriate cat in the array of cats
            }
            else
            {
                break; // if EOF then break
            }

            cats[i].average = 0; // clears garbage from locaiton
            // printf("%f I am the average score before for loop \n", cats[i].averageScore = 0);
            // loops through all three judge scores

            scanf("%d", &cats[i].score1); // saves each judges score into their respective slot in the array
            scanf("%d", &cats[i].score2); 
            scanf("%d", &cats[i].score3); 

            cats[i].average = cats[i].score1 + cats[i].score2 + cats[i].score3;

            cats[i].average = cats[i].average / MAXJUDGES; // finds the average of the beauty score and saves it to the appropriate slot.
        }
    }
}
int getCutestCat(struct cat *cats, int n)
{
    float highestScore = 0;      // tracks highest score
    float highestScoreIndex = 0; // tracks highest scores index
    for (int i = 0; i < n; i++) // loops through the number of cats
    {

        if (cats[i].average > highestScore) // if the highest score of the current cat is higher than the highestscore then save the new highest score
        {
            highestScore = cats[i].average;
            highestScoreIndex = i;
        }
    }

    return highestScoreIndex; // returns index to be saved for later use
}
void findLetterUsage(struct cat *c, int *n, struct KeyValuePair *letters) // used to find the occurance of each letter
{
    for (int i = 0; i < MAXLETTERS; i++) // loops through number of letters
    {
        for (int j = 0; j < *n; j++) // loops through number of cats
        {
            if (c[j].catName[0] == letters[i].key[0]) // if the first letter matches the letter in the array
            {
                letters[i].value += 1; // then add one to the value
                                       
            }
        }
        if (*n > 0)
        {
            letters[i].percentage = ((float)letters[i].value / *n) *100; // computes the percantage of each letter
        }
    }
}
void printData(int *n, int cutestCatIndex)
{
    for (int i = 0; i < *n; i++)
    {
        printf("%d %s %d %d %d %.2f\n",
               cats[i].cat_ID,
               cats[i].catName,
               (int)cats[i].score1,
               (int)cats[i].score2,
               (int)cats[i].score3,
               cats[i].average);
    }
    printf("Cutest cat is %s\n", cats[cutestCatIndex].catName);

    for (int i = 0; i < MAXLETTERS; i++)
    {
        printf("%s: %d %.2f%%\n", Letters[i].key, Letters[i].value, Letters[i].percentage);
    }
}
