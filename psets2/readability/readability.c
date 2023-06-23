/*
For this problem, you’ll implement a program that calculates
    the approximate grade level needed to comprehend some
    text, per the below.
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string sample_text);
int count_words(string sample_text);
int count_sentences(string sample_text);
void print_grade_level(int raw_score);

int main(void)
{
    string sample_text = get_string("Text: ");
    int L = count_letters(sample_text);
    int W = count_words(sample_text);
    int S = count_sentences(sample_text);
    /*
    Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
        where L is the average number of letters per 100
        words in the text, and S is the average number of
        sentences per 100 words in the text.
    */
    printf("letters %i\n", L);
    printf("words %i\n", W);
    printf("sentences %i\n", S);
    // I added the 0.5 so that when it's truncated, it'll round up after truncation.
    int grade = (0.0588 * (L * 100.0 / W) - 0.296 * (S * 100.0 / W) - 15.8) + 0.5;
    printf("grade%i\n", grade);
    print_grade_level(grade);
}

// Calculate number of letters.
int count_letters(string sample_text)
{
    int cnt = 0;
    // https://manual.cs50.io/#string.h
    for (int i = 0, n = strlen(sample_text); i < n; i++)
    {
        // https://manual.cs50.io/#ctype.h
        if (isalnum(sample_text[i]))
        {
            cnt += 1;
        }
    }
    return cnt;
}

// Calculate number of words.
int count_words(string sample_text)
{
    int cnt = 0;
    // https://manual.cs50.io/#string.h
    for (int i = 0, n = strlen(sample_text); i < n; i++)
    {
        if ((sample_text[i]) == ' ')
        {
            cnt += 1;
        }
    }
    return cnt + 1;
}

// Calculate number of sentences.
int count_sentences(string sample_text)
{
    int cnt = 0;
    // https://manual.cs50.io/#string.h
    for (int i = 0, n = strlen(sample_text); i < n; i++)
    {
        if (sample_text[i] == '.' ||
            sample_text[i] == '!' ||
            sample_text[i] == '?'
           )
        {
            cnt += 1;
        }
    }
    return cnt;
}

// Determines the grade level and prints it.
void print_grade_level(int grade)
{
    if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}
