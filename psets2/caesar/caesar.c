#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void print_cipher_text(string text, int cipher);

int main(int argc, string argv[])
{
    // Ensure there's exactly 1 cipher.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Iterate through each letter and run checks.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // Ensure all characters are numbers.
        // https://manual.cs50.io/3/isdigit
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        // Ensure the value is a non-negative integer.
        else if ((argv[1][i]) < 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Get text to be ciphered.
    string plaintext = get_string("plaintext: ");
    // Rotate plaintext based on the cipher and print.
    // https://manual.cs50.io/3/atoi
    print_cipher_text(plaintext, atoi(argv[1]));
}

void print_cipher_text(string text, int cipher)
{
    // Use formula c = (p + k) % 26 to cipher with key k.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // https://manual.cs50.io/3/isupper
        if (isupper(text[i]))
        {
            // ASCII Reference: A:Z = 65:90
            text[i] = 65 + (text[i] - 65 + cipher) % 26;
        }
        // https://manual.cs50.io/3/islower
        else if (islower(text[i]))
        {
            // ASCII Reference: a:z = 97:122
            text[i] = 97 + (text[i] - 97 + cipher) % 26;
        }
    }
    printf("ciphertext: %s\n", text);
}
