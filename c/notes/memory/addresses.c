#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int n = 50;

    // & - Print memory address of a variable
    // %p - pointer
    //printf("%p\n", &n);

    // * - go to an address, show what value is stored there
    //printf("%i\n", *&n);

    // Store the address of a value in a pointer
    // Pointer - denoted with star
    // int simply shows that it contains a pointer (address) to an int
    int *p = &n;
    //printf("%p\n", p);

    // Print the value at the pointer p, %i shows it will be an int
    //printf("%i\n", *p);


    // string - you really just create a pointer to the memory address of the first char
    char *s ="EMMA";
    printf("%s\n", s);

    // Print first char by using %c (*s is just a pointer to first char)
    printf("%c\n", *s);
    // print second char, etc.
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
    printf("%c\n", *(s+3));
    
    // Copy string
    // malloc - Memory allocation - allocating 5 bytes of memory
    // You need one more byte than the length bc of null terminator
    char *t = malloc(strlen(s) + 1);
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    printf("%s\n", t);
    
    // free - release memory
    // valgrind - find memory leaks
    free(t);
}

