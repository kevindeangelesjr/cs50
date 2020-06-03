#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Ensure that exactly one argument was provided, exit otherwise
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // Check that the provided key is exactly 26 characters long, exit otherwise
    string key = argv[1];
    int key_len = strlen(key);
    if (key_len != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;        
    }

    // Make sure key only contains alphabetic characters, exit otherwise
    for (int i = 0; i < key_len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetical characters\n");
            return 1;    
        }
    }

    // Get plaintext to encrypt
    string plaintext = get_string("plaintext: ");
    int plaintext_len = strlen(plaintext);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    printf("ciphertext: ");

    // Loop through each character of the plaintext provided
    for (int i = 0; i < plaintext_len; i++)
    {
        // Check if current character is alphabetical
        if (isalpha(plaintext[i]))
        {
            // Loop through the alphabet.  Compare each letter of the alphabet to the current character
            for (int ii = 0; ii < 26; ii++)
            {    
                // If the current character matches the current place in the alphabet
                if (tolower(plaintext[i]) == alphabet[ii])
                {
                    // Output the letter's place in the provided key, preserve case
                    if (isupper(plaintext[i]))
                    {
                        printf("%c", toupper(key[ii]));
                    }
                    else
                    {
                        printf("%c", tolower(key[ii]));
                    }
                }
            }
        }

        // If the current character is not alphabetical, simply output the character from the plaintext
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    // Print newline and return 0
    printf("\n");
    return 0;
}