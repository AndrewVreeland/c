/*
    ^ swapping technique


    ^ used helper array
    1. List permutations as all the ordering from 0 to n-1
    n = 3
    0 , 1 , 2

    1) an array with a partially filled in permutation
    2) a used array, storing which items have been partially filled 1 is fixed 0 is untouched
    3) an int k representing how many items have been fixed
*/

#define SIZE 4

void print(int *A, int n, char arr[][50])
{

    for (int i = 0; i < n; i++)
    {
       
            printf("%d", A[i]);
            printf("%s", arr[A[i]]);
            printf("\n");
        
    }
}

int main(void)
{
    int perm[SIZE] = {0};
    int used[SIZE] = {0};
    char arr[][50] = {"a", "b", "c", "d"};
    printperms(perm, used, 0, SIZE, arr);
    return 0;
}

void printperms(int *perm, int *used, int k, int n, char arr[][50])
{
    if (k == n)
    {
        print(perm, n, arr);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i]) // if i not used
        {
            used[i] = 1; // mark that it is used
            perm[k] = i; // transfer i to the perm array at kth
            
            printperms(perm, used, k + 1, n, arr); // increase k and grow further

            used[i] = 0;
        }
    }
}

/*
    ^ recursive
    1.) check if k is equal to n, the length of our permutation array
    2.) if not iterate through each un_used item, placing it in slot k ( in numerical order), and recurssively calling the function
    3.) noting that k+1 items are fixed.
*/