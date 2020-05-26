#include <stdio.h>
#include <cs50.h>

// Argc: argument count, argv: array of arguments to program
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("No arguments provided\n");
        // Bad return code
        return 1;
    }
    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
        // good return code
        return 0;
    }
    else
    {
        printf("hello, world\n");
        // good return code
        return 0;
    }
}