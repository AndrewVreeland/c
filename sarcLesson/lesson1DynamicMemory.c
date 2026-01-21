#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_ITEMS 2

juice_case *create_case(char *name, int numBottles);
void createAndPrintJuice();

typedef struct juice_case
{
    char name[128];
    int num_bottles;
} juice_case;


int main()
{
    createAndPrintJuice();
    return 0;
}

juice_case *create_case(char *newName, int numBottles)
{
    juice_case *newCase = malloc(sizeof(juice_case));
    strcpy(newCase->name, newName);
    newCase->num_bottles = numBottles;
    return newCase;
}

void createAndPrintJuice()
{
    char name[10] = "apple";
    int numOfBottles = 10;
    juice_case *case1 = create_case(name, numOfBottles);

    printf("name of Juice: %s and name of num of bottles: %d \n", case1->name, case1->num_bottles);
}
