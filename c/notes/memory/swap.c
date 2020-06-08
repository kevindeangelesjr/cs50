#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);

    // Pass in the MEMORY ADDRESSES - swap function will perform operations on these same values in memory
    swap(&x, &y);
    printf("x is %i, y is %i\n", x, y);
}

void swap(int *a, int *b)
{
    // Use pointers - go to memory address that was passed in
    int tmp = *a;
    *a = *b;
    *b = tmp;
}