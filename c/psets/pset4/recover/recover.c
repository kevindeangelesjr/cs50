#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Ensure exactly one command line argument was supplied
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open provided image file read-only
    FILE *imageFile = fopen(argv[1], "r");

    // Exit if image file could not be opened
    if (imageFile == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    // Keep track of number of files that have been recovered, for purposes of output file naming
    int recoveredCount = 0;

    // Boolean to check if the current JPG header found is the first found in the file
    int isFirst = 0;

    // Set up buffer char array to read 512 bytes at a time (block size for FAT)
    unsigned char buffer[512];

    // Var to iterate through each 512 byte chunk of the file
    int read = 0;

    // Var of FILE type to store name of the output file for the current JPG.  Will be updated as each new JPG is found
    FILE *outfile = NULL;

    // Allocate 8 bytes to filename for each JPG file.  Will be updated each time a new JPG is found
    char *filename = malloc(8);

    // Load next 512 bytes into the buffer array from the provided image file.
    // Continue looping while there are still bytes left in the file to read
    while ((read = fread(buffer, 512, 1, imageFile)) > 0)
    {
        // Check if first 4 bytes match JPG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // First JPG found
            if (isFirst == 0)
            {
                // Update filename for current JPG file, open a file with that name, and write current 512 bytes
                sprintf(filename, "%03i.jpg", recoveredCount);
                outfile = fopen(filename, "w");
                fwrite(buffer, 512, 1, outfile);

                // Update isFirst so that this block is not hit again
                isFirst++;
            }

            // Every other JPG file (header) found besides the first one
            else
            {
                // Close previous JPG file that was being written to
                fclose(outfile);

                // Update filename for current JPG file, open a file with that name, and write current 512 bytes
                recoveredCount++;
                sprintf(filename, "%03i.jpg", recoveredCount);                
                outfile = fopen(filename, "w");
                fwrite(buffer, 512, 1, outfile);
            }
        }

        // If a JPG header is not found at the beginning of the current 512 byte chunk
        else
        {
            // Simply move to next iteration of while loop if there is no JPG file currently open
            if (outfile == NULL)
            {
                continue;
            }
            
            // If a JPG file is currently open (implying we are still within a JPG file) write the current 512 byte chunk to it
            else
            {
                fwrite(buffer, 512, 1, outfile);
            }
        }
    }

    // Close all files and free up allocated memory
    fclose(outfile);
    fclose(imageFile);
    free(filename);
}
