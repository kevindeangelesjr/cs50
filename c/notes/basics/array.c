#include <stdio.h>
#include <cs50.h>

// Global variables
// Make variable constant - cannot change
//const int N = 3;

// Prototype - show c function that is implemented below main
float average(int length, int array[]);

int main (void)
{
    //int scores[N];
    //scores[0] = 72;
    //scores[1] = 73;
    //scores[2] = 33;
    //printf("Average: %i\n", (scores[0] + scores[1] + scores[2]) / N);


    int n = get_int("Number of scores: ");
    int scores[n];
    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Score %i: ", i + 1);
    }

    // Show 1 decmial point of float
    printf("Average: %.1f\n", average(n, scores));
}

// Function
float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }

    return (float) sum / (float) length;
}