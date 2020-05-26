#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    string s = get_string("Input: ");
    printf("Output: ");    

    // Iterate through each character in string
    //for (int i = 0; s[i] != '\0'; i++)

    // using string.h library
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        printf("%c", s[i]);
    }

    printf("\n");
}