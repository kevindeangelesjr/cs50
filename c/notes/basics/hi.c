#include <stdio.h>

int main(void)
{
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';

    // Convert chars (cast) to ints to view ASCII code.  Will also be done implicitly if you leave out (int)
    printf("%i %i %i\n", (int) c1, (int) c2, (int) c3);
}