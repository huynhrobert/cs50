/*
Determine how long it takes for a population to reach a particular
    size.
Say we have a population of n llamas. Each year, n / 3 new llamas are
    born, and n / 4 llamas pass away.
Complete the implementation of population.c, such that it calculates
    the number of years required for the population to grow from the
    start size to the end size.
Your program should first prompt the user for a starting population
    size.
If the user enters a number less than 9 (the minimum allowed
    population size), the user should be re-prompted to enter a
    starting population size until they enter a number that is
    greater than or equal to 9. (If we start with fewer than 9
    llamas, the population of llamas will quickly become stagnant!)
Your program should then prompt the user for an ending population
    size.
If the user enters a number less than the starting population size,
    the user should be re-prompted to enter an ending population
    size until they enter a number that is greater than or equal
    to the starting population size. (After all, we want the
    population of llamas to grow!)
Your program should then calculate the (integer) number of years
    required for the population to reach at least the size of the
    end value.
Finally, your program should print the number of years required
    for the llama population to reach that end size, as by printing
    to the terminal Years: n, where n is the number of years.
*/

#include <cs50.h>
#include <stdio.h>

int get_start_pop(void);
int get_end_pop(int start);


int main(void)
{
    // TODO: Prompt for start size
    int start = get_start_pop();
    // TODO: Prompt for end size
    int end = get_end_pop(start);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (start < end)
    {
        // Based on the assignment, population grows by 1/3 and
        // reduces by 1/4 each year.
        start += (start / 3 - start / 4);
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}

// Get the starting population from the user.
int get_start_pop(void)
{
    int n;
    do
    {
        n = get_int("What's the starting population size? ");
    }
    while (n < 9);
    return n;
}

// Get the ending population from the user.
int get_end_pop(int start)
{
    int n;
    do
    {
        n = get_int("What's the ending population size? ");
    }
    while (n < start);
    return n;
}
