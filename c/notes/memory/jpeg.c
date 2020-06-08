#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc !=2)
    {
        return 1;
    }

    // open file
    FILE *file = fopen(argv[1], "r");
    
    // if can't be open
    if (file == NULL)
    {
        return 1;
    }

    // Read 3 bytes from file
    unsigned char bytes[3];
    fread(bytes, 3, 1, file);

    // Check if bytes are 0xff 0xd8 0xff
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("Maybe\n");
    }
    else
    {
        printf("No\n");
    }
    
}