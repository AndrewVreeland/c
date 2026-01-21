#include <stdio.h>
#include <string.h>

typedef struct student
{
    char *lname; // this will require DMA to store a string
    int assignment;
    int finalExam;
    int total;
    int *quizzes; // this will require DMA to store quizzes
} student;

student **readCourses(int *numOfCourses, int *numOfStudents, int *numOfQuizes);
void release_memroy(student **student, int numOfCourses, int numOfStudents, int numOfQuizes);

int main()
{
    // atexit(report_mem_leak); // for memory leak detector.

    student **courseList;
    int i, j, C, N, M;
    
    courseList = readCourses(&C, &N, &M);
    printHighestTotal(courseList, C, N, M);
    release_memroy(courseList, C, N, M);
    
    return 0;
}

student **readCourses(int *numOfCourses, int *numOfStudents, int *numOfQuizes)
{

    student **courses = malloc(sizeof(*courses) * *numOfCourses);

    for (int i = 0; i < *numOfCourses; i++)
    {
        int tempTotal = 0;
        int tempNum = 0;
        char tempLName[51];

        for (int j = 0; j < *numOfStudents; j++)
        {
            courses[i] = malloc(sizeof(courses));
            scanf("%s", tempLName);

            courses[i][j].lname = malloc(strlen(tempLName) + 1);
            strcpy(courses[i][j].lname, tempLName);

            scanf("%d", &tempNum);
            tempTotal += tempNum;

            scanf("%d", &tempNum);
            tempTotal += tempNum;

            for (int k = 0; k < *numOfQuizes; k++)
            {
                scanf("%d", &tempNum);
                tempTotal += tempNum;

                courses[i][j].quizzes[k] = malloc(sizeof(int) * *numOfQuizes);
                courses[i][j].quizzes[k] = tempNum;
            }
            courses[i][j].total = tempTotal;
        }
    }
}

void release_memroy(student **student, int numOfCourses, int numOfStudents, int numOfQuizes)
{
    for (int i = 0; i < numOfCourses; i++)
    {
        for (int j = 0; j < numOfStudents; j++)
        {
            free(student[i][j].quizzes);
            free(student[i][j].lname);
        }
        free(student[i]);
    }
    free(student);
}