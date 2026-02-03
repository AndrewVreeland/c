#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_MAX 50;

typedef struct student
{
    char *lname;
    int assignment;
    int finalExam;
    int total;
    int *quizzes;
}student;

student** readCourses(int *C, int *N, int *M);

void release_memroy(student **st, int C, int N, int M);

int main()
{
    // atexit(report_mem_leak);
    student **courseList;
    int i, j, C, N, M;

    courseList = readCourses(&C, &N, &M);

    printHighestTotal(courseList, C, N, M);
    release_memroy(courseList, C, N, M);
    return 0;
}

student** readCourses(int *C, int *N, int *M)
{
    char tempLName[50];
    scanf("%d, %d, %d", C, N, M);
    student ** courses = malloc(*C *sizeof(student*));
    for(int i =0; i< C; i++)
    {
        courses[i] = malloc(*N * sizeof(student));
        for(int j; j < *N; j++)
        {
            int total =0;
            scanf("%s", tempLName);

            int nameLength = strlen(tempLName)+1;
            courses[i][j].lname = malloc(nameLength * sizeof(char));
            strcpy(courses[i][j].lname, tempLName);

            scanf("%d", &courses[i][j].assignment);
            total += courses[i][j].assignment;

            courses[i][j].quizzes = malloc(*M * sizeof(int));
            for(int k = 0; k < *M; k++)
            {
                scanf("%d", &courses[i][j].quizzes[k]);
                total += courses[i][j].quizzes[k];
            }

            scanf("%d", &courses[i][j].finalExam);
            total += courses[i][j].finalExam;
            courses[i][j].total = total;
        }
    }
return courses;
}

void printHighestTotal(student** courses, int C, int N, int M)
{
    int maxTotal = -1;
    int maxCourseIDX = 0;
    int maxStudentIDX = 0;

    for (int i =0; i < C; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(courses[i][j].total >maxTotal)
            {
                
            }

        }
    }
}