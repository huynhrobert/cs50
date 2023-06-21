/*
Rules to classify Amex vs MC vs Visa
American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.

All American Express numbers start with 34 or 37; most
MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers
    which we won’t concern ourselves with for this problem); and all
Visa numbers start with 4.

Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’
digits together. Add the sum to the sum of the digits that weren’t multiplied by 2. If the total’s last digit
is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
*/

#include <cs50.h>
#include <stdio.h>

long get_card_number(void);
int get_card_length(long card);
int calc_checksum(long card);
void determine_card_type(long card);

int main(void)
{
    long n = get_card_number();
    determine_card_type(n);
}

// Ask for card number.
long get_card_number(void)
{
    long n;
    do
    {
        n = get_long("What's the card number? ");
    }
    while (n < 0);
    return n;
}

// Iterate through the card to get length.
int get_card_length(long card)
{
    int n = 0;
    do
    {
        card = card / 10;
        n++;
    }
    while (card > 0);
    return n;
}

/*
Input: the card number.
Checksum calculation:
1. Multiply every other digit by 2, starting with second-to-last digit.
2. Add those products' digit together.
3. Add the sum to the sum of the digits that weren't multiplied by 2.
Output: the last digit of the checksum (should equal 0 to be valid).
*/
int calc_checksum(long card)
{
    long card2 = card;
    int even_digits = 0;
    int odd_digits = 0;
    int n;
    do
    {
        // Added % 10 and / 10 to separate out 12 into 1 and 2 which should be added as 3, not 12.
        even_digits = even_digits + ((2 * (card % 100 / 10)) % 10 + (2 * (card % 100 / 10)) / 10);
        card = card / 100;
    }
    while (card > 0);
    do
    {
        odd_digits = odd_digits + (card2 % 10);
        card2 = card2 / 100;
    }
    while (card2 > 0);
    n = (even_digits + odd_digits) % 10;
    return n;
}

void determine_card_type(long card)
{
    // Check if the card is INVALID.
    if (
        // Check if the card has 13, 15, or 16 digits.
        (card <= 1e12 || card >= 1e17 || get_card_length(card) == 14) ||
        // Check if the card has a valid checksum that adds up to 0.
        (calc_checksum(card) != 0))
    {
        printf("INVALID\n");
    }
    // Check if the card is an AMEX card.
    else if (
        // AMEX must have 15 digits.
        get_card_length(card) == 15 &&
        // AMEX must also start with 34 or 37.
        ((int)(card / 1e13) == 34 || (int)(card / 1e13) == 37))
    {
        printf("AMEX\n");
    }
    // Check if the card is a VISA card.
    else if (
        // VISA must have 13 or 16 digits.
        (get_card_length(card) == 13 || get_card_length(card) == 16) &&
        // VISA must also start with a 4.
        ((int)(card / 1e12) == 4 || (int)(card / 1e15) == 4))
    {
        printf("VISA\n");
    }
    // Check if the card is a MASTERCARD card.
    else if (
        // MASTERCARD must have 16 digits.
        get_card_length(card) == 16 &&
        // MASTERCARD must also start with 51, 52, 53, 54, or 55.
        ((int)(card / 1e14) >= 51 && (int)(card / 1e14) <= 55))
    {
        printf("MASTERCARD\n");
    }
    // The card is not an AMEX, VISA, nor MASTERCARD.
    else
    {
        printf("INVALID\n");
    }
}
