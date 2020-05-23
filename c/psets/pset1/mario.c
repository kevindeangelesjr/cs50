#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");

    while (height <= 0 || height >= 9)
    {
        height = get_int("Height: ");
    }
    
    for (int counter = 0; counter < height; counter++)
    {
        int space_counter = 0;
        while (space_counter < height - counter)
        {
            printf(" ");
            space_counter++;
        }

        for (int counter2 = 0; counter2 <= counter; counter2++)
        {
            
            printf("#");
        }

        printf("  ");

        for (int counter3 = 0; counter3 <= counter; counter3++)
        {
            printf("#");
        }
        
        space_counter = 0;
        while (space_counter < height - counter)
        {
            printf(" ");
            space_counter++;
        }

        printf("\n");
    }
}