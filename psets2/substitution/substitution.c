#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string upper_cipher(string cipher);
void print_cipher_text(string text, string converted_cipher);

int main(int argc, string argv[])
{
    // Ensure there's exactly 1 cipher.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Ensure there's 26 characters.
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Iterate through each letter and run checks.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // Ensure all characters are letters.
        // https://manual.cs50.io/3/isalpha
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain only letter\n");
            return 1;
        }
        // Ensure there are no duplicates.
        else if (true)
        {
            int dupe_cnt = 0;
            for (int j = 0; j < n; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    dupe_cnt++;
                }
            }
            if (dupe_cnt > 1)
            {
                printf("Key cannot have duplicate letters\n");
                return 1;
            }
        }
    }
    // Get text to be ciphered.
    string plaintext = get_string("plaintext: ");
    // Upper the cipher and then print cipher text.
    print_cipher_text(plaintext, upper_cipher(argv[1]));
}

string upper_cipher(string cipher)
{
    for (int i = 0, n = strlen(cipher); i < n; i++)
    {
        // https://manual.cs50.io/3/toupper
        cipher[i] = toupper(cipher[i]);
    }
    return cipher;
}

void print_cipher_text(string text, string converted_cipher)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // https://manual.cs50.io/3/isupper
        if (isupper(text[i]))
        {
            // ASCII Reference: A:Z = 65:90
            text[i] = converted_cipher[text[i] - 65];
        }
        // https://manual.cs50.io/3/islower
        else if (islower(text[i]))
        {
            // ASCII Reference: a:z = 97:122
            text[i] = converted_cipher[text[i] - 97] + 32;
        }
    }
    printf("ciphertext: %s\n", text);
}
