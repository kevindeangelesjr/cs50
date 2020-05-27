#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    // Get text to evaluate
    string text = get_string("Text: ");

    // Get length of inputted text
    int len = strlen(text);

    // Instantiate counter variables.  Words starting at 1 because of last word not having space after it.
    int num_letters = 0;
    int num_words = 1;
    int num_sentences = 0;

    // Loop through each character in text
    for (int i = 0; i < len; i++)
    {

        // If the current character is a space, increment the num_words counter
        if (isspace(text[i]))
        {
            num_words++;
        }

        // If the current character is punctuation, increment the num_sentances counter
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            num_sentences++;
        }

        // Otherwise, increment num_chars counter because it is a regular letter
        else if (isalpha(text[i]))
        {
            num_letters++;
        }
    }

    // Calculate reading level using Coleman-Liau index
    float L = 100 * (float) num_letters / (float) num_words;
    float S = 100 * (float) num_sentences / (float) num_words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int rounded_index = round(index);

    // Print results
    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (rounded_index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", rounded_index);
    }
}