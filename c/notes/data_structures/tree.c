#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Represent binary search tree node
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

int main(void)
{

}


// Recursive search algorithm
bool search(node *tree)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (50 < tree ->number)
    {
        return search(tree->left);
    }
    else if (50 > tree ->number)
    {
        return search(tree->right);
    }
    else
    {
        return true;
    }

}