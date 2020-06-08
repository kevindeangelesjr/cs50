#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Create file object
    // a - append
    FILE *file = fopen("phonebook.csv", "a");

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    // Print file
    fprintf(file, "%s,%s\n", name, number);

    // close file
    fclose(file);
}