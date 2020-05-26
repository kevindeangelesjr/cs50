#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Using ctype library
        printf("%c", toupper(s[i]));

        //if (s[i] >= 'a' && s[i] <= 'z')
        //{
            // Subtract 32 from ASCII code to get to uppercase ASCII code
            //printf("%c", s[i] - 32);

        //}
        //else
        //{
        //    printf("%c", s[i]);
        //}  
    }
    printf("\n");
}