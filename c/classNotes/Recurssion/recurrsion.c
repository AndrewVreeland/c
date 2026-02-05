void rec1(int x)
{
    if (x == 0)
        return;

    printf("%d", x);
    rec(x - 1);
} // prints 4, 3 ,2 ,1

void rec2(int x)
{
    if (x == 0)
        return;

    rec(x - 1);
    printf("%d", x);
} // prints 1 2 3 4

int powerWithReccursion(int b, int e)
{
    if (e == 0)
    {
        return 1;
    }
    else
    {
        return (b * powerWithReccursion(b, e - 1));
        // multiplys from the bottom up the last value when e = 0 gets returned and is
        // used for the previous calls calculation
    }
} // exponentioal recursive function

int Power(int base, int exponents)
{
    long result = 1;
    while (exponents != 0)
    {
        result *= exponents;
        --exponents;
    }
    return result;
} // exponentioal without recussive function

/*

• Here are the two general constructs of recursive functions:
^   Construct 1
&   if (terminating condition)
&        {
*            DO FINAL ACTION
&        }
&   else {
*            Take one step closer to terminating condition
*            Call function RECURSIVELY on smaller subproblem
&       }
^       Construct 2
&   if (!(terminating condition) )
&       {
*           Take a step closer to terminating condition
*           Call function RECURSIVELY on smaller subproblem
&       }
?• Typically, functions that return values take on the first construct,
?• while void recursive functions use the second construct.
?• Note that these are not the ONLY layouts of recursive programs, just common ones

*/
// ^ construct1
int construct1Recurrsive(int n)
{
    if (n = 0)
    {
        return 0;
    }
    // TODO: 1+2 +.... n.
    return n + construct1Recurrsive(n - 1); //? this will count down from n to 0 then add them from 0 to n;
}

int factorialWithRecurssion(int n)
{
    if (n = 0)
    {
        return 1;
    }
    return n * factorialWithRecurssion(n - 1);
}

int fib(int n)
{
    if (n <= 1)
        return n;
    else
        return fib(n - 1) + fib(n - 2);
}

// ^ construct 2

/*

Let’s write a function to generate TIP chart:
• Write a function that takes in the lowest dollar value and highest dollar value on
the chart. You know the TIP rate. The method header would look like the:
 The function prints out a chart with the appropriate tips
 for meals ranging from first_val to last_val number of
 dollars, for every whole dollar amount. Both parameters
 must be positive integers.

*/

void Tip_Chart(int first_val, int last_val)
{
    if (!(first_val > last_val))
    {
        printf("On a meal of $%d", first_val);
        printf(" you should tip $%lf\n", first_val * 0.25);
        Tip_Chart(first_val + 1, last_val);
    }
}

//! LOOK OVER THIS WILL BE ON TEST
void print_reverse(char string[], int n) //! if you print after recurrsion we wont print till the end
{
    // if n == 0 return;
    // print st[n-1]
    // pr(st, n-1)
}

// this function here does not work with negatives
int multiplicitiveRecurssiveFunction(int firstNum, int secondNum)
{
    if ((firstNum == 0) || (secondNum == 0))
    {
        return 0;
    }
    else
    {
        return (firstNum + multiplicitiveRecurssiveFunction(firstNum, secondNum - 1));
    }
}

int multiplicitiveRecurssiveFunction2(int firstNum, int secondNum)
{
    if (secondNum < 0)
    {
        return -multiplicitiveRecurssiveFunction2(firstNum, -secondNum);
    }
    else if (firstNum < 0)
    {
        return -multiplicitiveRecurssiveFunction2(-firstNum, secondNum);
    }
    else if ((firstNum == 0) || (secondNum == 0))
    {
        return 0;
    }
    else
    {
        return (firstNum + multiplicitiveRecurssiveFunction(firstNum, secondNum - 1));
    }
}


convertBinaryRecurssion(int n)
{
    if(n = 0)
    {
        return 0;
    }
    else
    {
        convertBinaryRecurssion(n/2);
        printf("%d", n%2); // this will print the binary from the bottom up
    }

}

void recurssionTowersOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{

    /*
    Three rods 
    must move disks from rod 1 to rod 3 
    you cannot put bigger disk on smaller disk
    you may only move one disk at a time 
    */

    if (n ==1 )
    {
        printf("move disk 1 from rod %c to rod %c", from_rod, to_rod);
    }
    recurssionTowersOfHanoi(n-1, from_rod, aux_rod, to_rod);
    printf("");
}


int f(int n)
{
    int ans;
    int i;
    if(n <3)
    return n;
    ans = f(n/2);
    for(i = 0; i <n; i ++)
    {
        ans += f(i);
        return ans;
    }
}

