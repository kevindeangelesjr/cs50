#include <stdio.h>

int main (void)
{
    int x = 1;
    int y = 2;

    if (x < y)
    {
        printf("y is greater than x\n");
    }
    else if (x > y)
    {
        printf("x is greater than y\n");
    }
    else
    {
        printf("x is equal to y\n");
    }
    
}