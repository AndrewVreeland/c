
#include <stdio.h>

/* 
Red (!)
Blue (?)
Green (*)
Yellow (^)
Pink (&)
Purple (~)
Mustard (todo)
Grey (//)
*/


void callocMalloc();

typedef struct Student
{
    int grade;

}Student;

int main()
{
    callocMalloc();
}

void callocMalloc()
{
    int *a = malloc(10 * sizeof(int));
    for(int i =0; i <10; i++)
    {
        printf("%d", a[i]);
    }

    int *b = calloc(10, sizeof(int));
    for(int i = 0; i< 10; i++)
    {
        printf("%d", a[i]);
    }
}

Student dynamicStruct(Student *student, int num)
{
    student = calloc(num, sizeof(Student));
}

