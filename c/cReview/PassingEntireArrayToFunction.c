
void incBy2 (int *a, int n);

int main()
{
    int num[] = {24, 34, 12, 44, 56, 17};
    int arrayLength = sizeof(num) / sizeof(num[0]);

    printf("Original Array: \n");

    printf("%d \n", arrayLength);

    for (int i = 0; i < arrayLength; i++)
    {
        printf(" array value %d: %d\n", i, num[i]);
    }

    incBy2(num, arrayLength );
    
    printf("\n Array after calling incrementBy2: \n\n");
    for(int i = 0; i < sizeof(num)/sizeof(num[0]); i++)
    {
        printf("Array value after %d: %d \n", i, num[i]);
    }

}

void incBy2 (int *a, int n)
{
    for(int i = 0; i < n; i++)
    {
        *a = *a + 2; // increments element by 2
        a++; 
    }
}