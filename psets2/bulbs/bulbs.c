/*
Each sequence of bulbs, though, encodes a message in binary,
    the language computers “speak.” Let’s write a program to
    make secret messages of your own, perhaps that we could
    even put on stage!
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void convert_msg(string msg);
int get_int_len(int integer);

int main(void)
{
    // TODO
    string msg = get_string("Message: ");
    convert_msg(msg);
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

// Iterate through the card to get length.
int get_int_len(int integer)
{
    int n = 0;
    do
    {
        integer = integer / 10;
        n++;
    }
    while (integer > 0);
    return n;
}

void convert_msg(string msg)
{
    // Loop through each letter.
    for (int i = 0, n = strlen(msg); i < n; i++)
    {
        // Create the right portion of the 8-bit.
        int int_bits = 0;
        for (int j = 0; j < 8; j++)
        {
            // Convert between base 10 to base 2.
            // https://manual.cs50.io/3/pow
            if ((int)(msg[i] / pow(2, j)) % 2 != 0)
            {
                int_bits += 1 * pow(10, j);
            }
        }
        // Calculate how many 0s to add.
        int int_len = get_int_len(int_bits);
        // Print left side.
        for (int k = 0; k < 8 - int_len; k++)
        {
            print_bulb(0);
        }
        // Print right side.
        for (int l = 0; l < int_len; l++)
        {
            print_bulb((int)(int_bits / pow(10, int_len - 1 - l)) % 10);
        }
        printf("\n");
    }
}
