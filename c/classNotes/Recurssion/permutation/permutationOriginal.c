/*
   ! PAGE 4 BLACK notebook has more specific notes 
*/

#define SIZE 4

void print(int *A, int n)
{

    for (int i = 0; i < n; i++)
    {
       
            printf("%d", A[i]);
            printf("\n");
        
    }
}

int main(void)
{
    int perm[SIZE] = {0};
    int used[SIZE] = {0};
    printperms(perm, used, 0, SIZE);
    return 0;
}

void printperms(int *perm, int *used, int k, int n)
{
    if (k == n)
    {
        print(perm, n);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i]) // if i not used
        {
            used[i] = 1; // mark that it is used
            perm[k] = i; // transfer i to the perm array at kth
            
            printperms(perm, used, k + 1, n); // increase k and grow further

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