/*

! Strings review
* • String is a char array
* • Sequence of zero or more characters
    terminated by null (‘\0’) character
* • Note that ‘\0’ terminates the string but it is
    not part of the string.
* • strlen() function returns the length of a string.
    null is not part of the length
* • there are many useful functions for strings
    are available at string.h
! char s[10] = “cat”;
* • Here s is an string and 10 bytes are allocated for the
    string or array.
* • Also can be declared using pointer:
! char *s = “cat”;
* but you cannot change the content in this
    case. We have to use dynamic memory allocation to work on
    it.
* You can access each character in the string like an
    array.


    ! You can pass string to a function in the same way you
    pass an array.
* • You can use scanf and gets method for taking
    string input
* • Be careful while using scanf to read string as it
    will skip anything after space


*/
#include <stdio.h>
#include <string.h>
void stringLogic();
void stringNameLogic();


int main()
{
    char name[20];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Your name is %s.", name);

    char name1[30];
    printf("Enter name: ");
    gets(name1); // read string
    printf("Name: ");
    puts(name1);

    int id;
    char name2[30];
    char ch, c;
    while (1)
    {
        printf("\nMenu, e: enter, x: exit: ");
        scanf("%c", &ch);
        if (ch == 'x')
        {
            printf("\n<<<<<<<EXIT>>>>>>\n\n\n");
            break;
        }
        if (ch == 'e')
        {
            printf("\nEnter student id: ");
            scanf("%d", &id);
            printf("\nEnter student name: ");
            scanf("%s[^\n]s", name2);
            printf("Your entered %d %s", id, name2);
        }
    }
    printf("----------------\n");
    stringLogic();
    stringNameLogic();

    return 0;
}

/*

Output:
Enter name: Nusair Ahmed
Your name is . Nusair
! see it failed to keep Ahmedin the string
* • gets and puts methods for string.
* • If you use gets, it can take string with spaces.
*/

/*

* • gets() method is dangerous as it does not care about the
    size of the char array and can takes more than the size.
    As a result your program can crash and become unsafe.
* • Alternative:
    char name[30];
    printf("Enter name: ");
    scanf("%[^\n]s",name);
* • you can also use: fgets(name, sizeof(name),
    stdin);
* • In case of fgets, it also keep the ‘\n’ in the string. The following
    line will remove that ‘\n’
* • name[strcspn(name, "\n")] = 0;
* • See uploaded example code: fgets_DifferentScanf.c
* • You will also get explanation in the code

*/

void stringLogic()
{
    char dog[10] = "rosco";
    char dog2[10] = "cooper";
    int length = strlen(dog);
    printf("%d \n", length); // determines string length
    strcat(dog, dog2); // adds dog2 to the end of dog
    strcpy(dog, dog2); // coppies dog 2 into dog
    strcmp(dog, dog2); // compares string -- returns 0 if the same -- negative if first character is less than second 
    // positive if greater then second
    strstr(dog, dog2); //finds a subString
    // strlwr(dog); // converts string to lowercase
    // strupr(dog); // converts to upper
    // strrev(dog); // reverses string

}

void stringNameLogic()
{
    char fname[100], lname[100];
    char fullname[100];
    printf("Enter your first name! \n");
    scanf("%s", fname);

    printf("Enter your last name! \n");
    scanf("%s", lname);

    printf("The length of your first name is %lu \n", strlen(fname));
    printf("The length of your first name is %lu \n", strlen(lname));
    if(strcmp(fname, lname) < 0)
    {   
        printf("%s comes before %s \n", fname, lname);
    }else if(strcmp(fname, lname) > 0)
    {
        printf("%s comes before %s \n", lname, fname);
    }else{
        printf("%s and %s are alphabetically the same \n");
    }

    printf("First name = %s and Last name = %s \n", fname, lname);
    strcat(fname, " ");
    strcat(fname, lname);
    printf("name = %s \n", fname);

    strcpy(fullname, fname);
    printf("This is your full name %s \n", fullname);

    char key[50];
    scanf("%s", key);
    
    if(strstr(fullname, key) != NULL){

        printf("%s \n", strstr(fullname, key));
    }else {
        printf("There is no match \n");
    }

    
}