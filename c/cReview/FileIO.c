#include <stdio.h>

int createAFile();
int readAFile();
int writeCharToFile();

int main()
{
    createAFile();
    readAFile();
    writeCharToFile();

    return 0;
}

int createAFile()
{
    FILE *file;

    // Creating a file
    file = fopen("file1.txt", "w");

    // Checking whether file is
    // created or not
    if (file == NULL)
    {
        printf("Error in creating file\n");
        return 1;
    }
    printf("File created.\n");
    fclose(file);
    printf("file closed");
    return 0;
}

int readAFile()
{
    FILE *file;

    // opening a file
    file = fopen("file1.text", "r");

    if(file == NULL)
    {
        printf("Error in opening file\n");
        return 1;
    }
    printf("File opened \n");
    fclose(file);
    printf("file closed");
    return 0;
}

int writeCharToFile()
{
    FILE *fp;
    char *string = "programming can be fun!";
    int i;
    char ch;

    fp = fopen("file1.text", "w");
    for(i = 0; i < strlen(string); i++)
    {
        ch = string[i];
        if (ch == EOF)
        {
            break;
        }
        fputc(ch, fp);
    }
}