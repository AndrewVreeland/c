typedef struct Book
{
    char title[50];
    float price;
    int pages;
    Author author;
} Book;

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct Author
{
    char authorName[50];
    char aurthorLanguage[50];
    Date dob;
} Author;

int main()
{
    Book dogHouse;
    dogHouse.price = 100;
    strcpy(dogHouse.title, "Dog House");
    dogHouse.pages = 10;

    Book *p1;
    p1 = &dogHouse;
    (*p1).price = 50;
    printf("%d \n", (*p1).price); // why does this not work?

    Book catHouse;
    catHouse.price = 100;
    strcpy(catHouse.title, "Cat House");
    catHouse.pages = 10;

    Book *p[10];
    p[0] = &dogHouse;
    p[1] = &catHouse;
    p[0]->price = 200;

    changeme(&p[0]);
    dogHouse = changemeV3(dogHouse);

    int myArr[] = {10, 20, 30, 40, 50};
    changeArray(myArr, sizeof(myArr) / sizeof(myArr[0])); // name of array passes the address of the first value

    for (int i = 0; i < sizeof(myArr) / sizeof(myArr[0]); i++)
    {
        printf("%d", myArr[i]);
    }
}

void changeme(Book *p)
{
    p->price = 10;
    return p;
}

Book changemeV3(Book p)
{
    p.price = 1000;
    p.pages = 100;
    return p;
}

void changeArray(int *a, int size) // arrays are always call by reference a[] will work aswell
{
    int i;
    for (i = 0; i < size; i++)
    {
        a[i] = 10;
    }
}

void setDate()
{
    Date d1;
    d1.year = 2021;
    scanf("%d", &d1.month);
}