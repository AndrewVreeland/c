void parkCar(int *garagearr, int row, int col);
void printParkingSpots();
int isSeatToken(int *seats, int row, int col, int totalCols);
void CinemaSeatingChart();
void DigitalPhotoFilter();
void brightenPixel(int *img, int row, int col, int totalCol);

int MY_GARAGE[3][4] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
int IMG[6][6] =
    {
        10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10,
        10, 10, 10, 10, 10, 10};

int main()
{

    parkCar((int *)MY_GARAGE, 2, 1);
    printParkingSpots();
    CinemaSeatingChart();
    brightenPixel((int *)IMG, 1, 3, 6);

    return 0;
}

void parkCar(int *garagearr, int row, int col)
{
    *(garagearr + (row * 4 + col)) = 1;
}

void printParkingSpots()
{
    for (int i = 0; i < sizeof(MY_GARAGE) / sizeof(MY_GARAGE[0]); i++)
    {
        printf("\n");
        for (int j = 0; j < sizeof(MY_GARAGE[0]) / sizeof(MY_GARAGE[0][0]); j++)
        {
            printf("%d ", MY_GARAGE[i][j]);
        }
    }
    printf("\n");
    printf("-------------\n");
}

/*
! How  *(garagearr + (row * 4 + col)) = 1; functions.
    1.
    * The Pointer (garagearr)
    * This is your starting point.
    * It is the memory address of the very first parking spot in the garage
    * (Row 0, Column 0). In your computer's RAM, it might be a number like 1000.
    2.
    * The Math (row * 4 + col)
    * row * 4: Since every row has 4 spots, if you want to go to Row 2,
    * you have to skip over 8 spots first (Row 0 and Row 1).+ col:
    * Once you are at the start of Row 2, you move forward by the number of columns
    * (the specific spot).Result: If row = 2 and col = 1, the math is $(2 \times 4) + 1 = 9$.
    3.
    * The Address Jump (garagearr + 9)
    * Now, the computer takes your starting address (1000)
    * and adds your offset. It "walks" forward 9 integer-sized steps.
    * Crucial point: It doesn't just add the number 9; it adds
    * 9 times the size of an integer (usually 36 bytes).
    * Now you are standing right in front of the correct mailbox.


*/

void CinemaSeatingChart()
{
    int THEATER_SEATS[5][10] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};

    int answer = isSeatToken((int *)THEATER_SEATS, 3, 4, 10);
    if (answer = 1)
    {
        printf("congrats seat is available \n");
        printf("-------------\n");
    }
    else
    {
        printf("seat is unavailable \n");
        printf("-------------\n");
    }
}

int isSeatToken(int *seats, int row, int col, int totalCols)
{
    return *(seats + (row * totalCols) + col);
}

void DigitalPhotoFilter()
{

    brightenPixel((int *)IMG, 1, 1, 6);
}

void brightenPixel(int *img, int row, int col, int totalCol)
{
    int pixelValue = *(img + (row * totalCol) + col);
    int finalPixelValue = 2 * pixelValue;
    *(img + (row * totalCol) + col) = finalPixelValue;

    for (int i = 0; i < sizeof(IMG) / sizeof(IMG[0]); i++)
    {
        for (int j = 0; j < sizeof(IMG[0]) / sizeof(IMG[0][0]); j++)
        {
            printf("%d ", IMG[i][j]);
        }
        printf("\n");
    }
}