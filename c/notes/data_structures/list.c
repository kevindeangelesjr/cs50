#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Create pointer to int 'list'
    // malloc to allocate enough memory for 3 integers (array).  Total of 12 bytes
    int *list = malloc(3 * sizeof(int));
    // Best pratice to always check after you allocate memory.  NULL would indicate system out of memory
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // If you want to make the array bigger
    // Allocate array of size 4 ints
    //int *tmp = malloc(4 * sizeof(int));
    //if (tmp == NULL)
    //{
    //    return 1;
    //}
    // Copy values from old array to new array
    //for (int i = 0; i < 3; i++)
    //{
    //    tmp[i] = list[i];
    //}
    //tmp[3] = 4;
    //free(list);
    //list = tmp;

    // simpler way to do the above (make an array bigger)
    // realloc - resize existing chunk of memory, automatically copies items from old to new
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        return 1;
    }
    list = tmp;
    tmp[3] = 4;


    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);
}