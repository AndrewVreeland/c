#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 50

typedef struct Advisor
{
    char name[MAXLEN+1]; //static array for name
    float point;
} Advisor;

typedef struct
{
  char *pName; //need DMA
  char **viewPoints; //DMA array of strings
  int vpCount;
  Advisor **advisors; //need DMA to piont to an array of advisor pointers
  int advCnt; //advisor count
  int *ratings; //array of ratings from the advisors

} NationalPark;

int main(void)
{
  return 0;
}

//this function create one advisor and returns this
Advisor* createOneAdvisor(char* name, float point)
{
    
  Advisor *tempAdvisor = malloc(sizeof(Advisor));
  strcpy(tempAdvisor->name, name);
  tempAdvisor ->point = point;
}

//this function returns an array of advisor pointers, where each pinter is pointint go a dynamically allocated advisor
Advisor** readAdvisorList(int *count)
{
  scanf("%d", count); // finds amount of advisors
  Advisor **advisorList = (*count * sizeof(Advisor*));

  for(int i =0; i < *count; i++)
    {
      char advName[MAXLEN+1];
      float point;
      scanf("%s %f", advName, point);
      createOneAdvisor(advName, point);
    }


  
}

//read and create an array of national park and load all the data
NationalPark* readNPArray(int *npCount, Advisor **advisorList, int advisorListCnt)
{
  
  
  
}

void freeAdvisors(Advisor **advisorList, int listCount)
{
  //free all the memory appropriately
}

void freeNatinalParks(NationalPark *parks, int parkCount)
{
  //free all memory appropriately
}

void displayNationalParks(NationalPark *parks, int parkCount)
{
    for (int i = 0; i < parkCount; i++)
    {
        printf("\n=====================================\n");
        printf("National Park: %s\n", parks[i].pName);
        printf("=====================================\n");

        /* View Points */
        printf("View Points (%d):\n", parks[i].vpCount);
        for (int j = 0; j < parks[i].vpCount; j++)
        {
            printf("  - %s\n", parks[i].viewPoints[j]);
        }

        /* Advisors and Ratings */
        printf("\nAdvisor Ratings:\n");
        for (int j = 0; j < parks[i].advCnt; j++)
        {
            printf("  %s (%.2f points): Rating = %d\n",
                   parks[i].advisors[j]->name,
                   parks[i].advisors[j]->point,
                   parks[i].ratings[j]);
        }
    }
}


int main(void) {
  int advisorCnt, parkCnt;