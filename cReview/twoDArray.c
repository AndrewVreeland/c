// !!!!!!!!!!!!!! MULII DIMENSIOONAL ARRAYS !!!!!!!!!!!!!!!!!!!!!

/*

• It is also possible to have array with two or more
dimensions
• 2 dimensional array also called a matrix and easy to
visualize in tabular form.
• An example declaration:
! int grid[4][2];
• This array as 4 rows and 2 columns. Can be seen as:
*        Colum 0   Column 1
* Row 0 grid[0][0] grid[0][1]
* Row 1 grid[1][0] grid[1][1]
* Row 2 grid[2][0] grid[2][1]
* Row 3 grid[3][0] grid[3][1]

The declaration int grid[4][2]; can also be
interpreted as:
• This is an array of 4 elements
– Each element is an array of 2 elements
• So, it is kind of 4 one-dimensional arrays.
• Example: grid[0] is an array of 2 elements
– grid[0][0], and grid[0][1]
• The elements are laid out sequentially in
memory, just like a one-dimensional array

*/

int main()
{
    int grid[4][2] = {
        {5, 6},
        {8, 23},
        {22, 9},
        {90, 4}};
    int i;
    for (i = 0; i <= 3; i++)
        printf("\nAddress of %d th 1-D array = %u", i, grid[i]);

    printf("\n----------");
    twoDArrayByPointer();
    return 0;
}

/*
!• The following are equivalent:
*• s[2][1] //second row, first col
*• *(s[2]+1)
*• *(*(s+2)+1) //here 2 indicates the array number

*/

void twoDArrayByPointer()
{
    int s[4][2] = {
        {5, 6},
        {8, 23},
        {22, 9},
        {90, 4}};

    for (int i = 0; i < sizeof(s) / sizeof(s[0]); i++)
    {
        printf("\n");
        for (int j = 0; j < sizeof(s[0]) / sizeof(s[0][0]); j++)
        {
            printf("%d ", *(*(s + i) + j));
        }
    }
}

/*

* • Only first subscript may be left unspecified
! • void f1(int grid[][10]) // valid
• void f3(int grid[][]); //invalid
• Generally, array sizes are also passed to functions while
dealing with 1D or multi dimensional array
! • void print( int a[ ][4], int row, int col )
• The sizes allow to iterate properly and access the elements
within the ranges.

*/

void twoDArrayByPointer2()
{
    int a[3][4] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 0, 1, 6};
}

void display(int *q, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d", *(q + i * col + j));
            printf("\n");
        }
        printf("\n");
    }
}

print(int q[][4], int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            printf("%d ", q[i][j]);
        printf("\n");
    }
    printf("\n");
}