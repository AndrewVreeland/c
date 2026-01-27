void rec1(int x)
{
    if(x ==0)
    return;

    printf("%d", x);
    rec(x-1);
} // prints 4, 3 ,2 ,1 

void rec2(int x)
{
    if(x ==0)
    return;

    rec(x-1);
    printf("%d", x);
}// prints 1 2 3 4

int p(int b, int e)
{
    return b*p(b, e-1);
} // exponentioal recursive function