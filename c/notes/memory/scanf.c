#include <stdio.h>

int main(void)
{
    //int x;
    //printf("x: ");
    // scanf - gives prompt and stores at address of x
    //scanf("%i", &x);
    //printf("x: %i\n", x);

    // only allocate 5 bytes memory - 4 chars and a null terminator
    char s[5];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}