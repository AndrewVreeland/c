/*
^           Linear Queue operations
        Max_Size = 6, Queue[Max_Size], Front = 0, Rear=0
    • EnQueue(char x): Queue[Rear++] = x,
    • DeQueue(): return Queue[Front++],
    • Peek(): return Queue[Front]

*/

void EnQueue(int x)
{
if( Rear < Max_Size)
{
Queue[Rear++] = x;
printf("Inserted");
}
else
printf("Full");
}

int DeQueue()
{
if(Front==Rear)
{
printf(“Empty“);
return -9999;
}
else
return Queue[Front++];
}