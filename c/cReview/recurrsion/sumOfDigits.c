int sumDigits(int n) // n = 167
{
    if(n % 10 == n) return n; // base case returns last digit

    int value = n % 10; // captures right most digit
    return value + sumDigits(n/10); // adds right most digit to future calls

}

