int main()
{

    int x, y;
    int *p1, *p2;
    x = -42;
    y = 163;
    p1 = &x;
    p2 = &y;
    printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("p2 = %p *p1 = %d \n", p2, *p2);
    printf("----------\n");

    *p1 = 17; // dereferencing. this means to put 17 to the address where p1 is pointing. this is now x = 17
    printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("-------------\n");

    p1 = p2; // p1 is not pointing to x anymore but is now poinging at y
    printf("p1 = %p *p1 = %d \n", p1, *p1);
    printf("-----------\n");

    p2 = &x; // p2 is now pointing at the value stored at x
    printf("p2 = %p, *p2 = %d\n ", p2, *p2);
    printf("----------\n");
    
    *p1 = *p2; // p1 points at the same address however, the value stored at p1 was overwritten with the value stored at p2 
    printf("p1 = %p, *p1 = %d \n", p1, *p1);
}