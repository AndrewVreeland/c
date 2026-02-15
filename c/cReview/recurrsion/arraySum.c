int sumArray(int arr[], int n)
{
    if (n == 0) return 0;

    return arr[n-1] + sumArray(arr, n-1);
}