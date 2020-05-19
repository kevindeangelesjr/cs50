#include <stdio.h>

// Tell c that function is later in the code
void cough(int n);

int main(void)
{
    cough(4);
}

// first void: returns no value, second void (now int n): takes no value
void cough(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("cough\n");
    }
}