#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_bricks(int size);

// My main function to get the size and print the bricks.
int main(void)
{
    int n = get_size();
    print_bricks(n);
}

// Asks for the desired pyramid size.
int get_size(void)
{
    int n;
    do
    {
        n = get_int("What's the desired pyramid size? ");
    }
    while (n <= 0 || n > 8);
    return n;
}

// Prints the pyramid (actually reused from mario-more).
void print_bricks(int size)
{
    for (int i = 0; i < size; i++)
    {
        // Make left side of the pyramid.
        for (int j = 0; j < (size - 1 - i); j++)
        {
            printf(" ");
        }
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
