#include <stdio.h>

int main (void)
{
    int i = 0;
    while (i < 50)
    {
        printf("hello, world!\n");
        i++;
    } 

    for (int counter = 0; counter < 50; counter++)
    {
        printf("Goodbye, world!\n");
    }
}