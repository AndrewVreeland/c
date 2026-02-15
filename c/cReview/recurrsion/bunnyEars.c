int numOfBunnyEars(int n)
{
    if (n == 0 ) return 0;

    return 2 + numOfBunnyEars(n -1);
}