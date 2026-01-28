#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 50


typedef struct Advisor{
    
    char name[MAXLEN+1];
    float point;
}Advisor;


typedef struct NationalParks
{
    char *pname; // need DMA
    char **viewPoints; // DMA
    int vpCount;
    Advisor **advisors; // DMA
    int advCnt;
    int *raitings; // DMA
}NationalParks;


Advisor* createOneAdvisor(char* name, float point);
Advisor** readAdvisorList(int *count);
NationalParks* readNPArray(int *npCount, Advisor **advisorList, int advisorListCnt);


Advisor** readAdvisorList(int *count)
{
    scanf("%d", count);
    Advisor **advList = malloc(*count * sizeof(Advisor*));

    for(int i = 0; i < *count; i++)
    {
        char advName[MAXLEN +1];
        float point;
        scanf("%s %f", advName, &point);
        advList[i] = createOneAdvisor(advName, point);
    }
}

Advisor* createOneAdvisor(char* name, float point)
{
    Advisor *adv = malloc(sizeof(Advisor));
    strcpy(adv ->name, name); // dont need malloc because space is already created within struct
    adv -> point = point;
    return adv;
}

NationalParks* readNPArray(int *npCount, Advisor **advisorList, int advisorListCnt)
{
    scanf("%d", npCount); // dont need & becuase np is a pointer
    NationalParks* npList = (*npCount * sizeof(NationalParks));
    for(int i = 0; i < *npCount; i++)
    {
        char tempName[MAXLEN+1];
        scanf("%s %d %d", tempName, &npList[i].vpCount, &npList[i].advCnt);
        int len = strlen(tempName) +1;
        npList[i].pname = (len * sizeof(char));
        strcpy(npList[i].pname, tempName);

        npList[i].viewPoints =(npList[i].vpCount * sizeof(char*));
        for(int j = 0; j << npList[i].vpCount; j++)
        {
            char vpName[MAXLEN +1];
            scanf("%s", vpName) +1;
            len = strlen(vpName) +1;
            npList[i].viewPoints = malloc(len * sizeof(char));
            strcpy(npList[i].viewPoints[j], vpName);
        }

        npList[i].raitings = malloc(npList[i].advCnt * sizeof(int));

        for(int j = 0; j < npList[i].advCnt; j++)
        {
            npList[i].raitings[j] = 1 + rand() % 10;
        }

       npList[i].advisors = malloc(npList[i].advCnt * sizeof(Advisor*));

       for (int j = 0; j < npList[i].advCnt; j++)
       {
        char tempAdvName[MAXLEN+1];
        scanf("%s", tempAdvName);

        for(int k = 0; k < advisorListCnt; k++)
        {
            if(strcmp (advisorList[k]->name, tempAdvName) == 0)
            {
               npList[i].advisors[j] = advisorList[k];
            } 
        }
       }
    }
    return npList;

}

int main (void)
{
    int advisorCnt, parkCnt;
    Advisor **advList = readAdvisorList(&advisorCnt);

    readNPArray(&parkCnt, advList, advisorCnt);
}