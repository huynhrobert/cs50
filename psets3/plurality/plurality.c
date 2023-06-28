#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // Loop through each candidate and check if it's a match.
    for (int i = 0; i < candidate_count; i++)
    {
        // https://manual.cs50.io/3/strcmp
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
// TODO

// Selection sort candidates by number of votes, descending order.
// Step 1: Loop from 0 to N - 1.
    for (int i = 0; i < MAX - 1; i++)
    {
        // Step 2: Find largest number between i and i - 1.
        int tmp_position = MAX - 1;
        for (int j = i; j < MAX - i - 1; j++)
        {
            if (candidates[j].votes > candidates[tmp_position].votes)
            {
                tmp_position = j;
            }
        }
        // Step 3: Swap the largest number with i.
        if (candidates[tmp_position].votes > candidates[i].votes)
        {
            candidate temp[1];
            // Step 3a: Store current candidate info.
            temp[0].votes = candidates[i].votes;
            temp[0].name  = candidates[i].name;
            // Step 3b: Assign largest to current candidate.
            candidates[i].votes = candidates[tmp_position].votes;
            candidates[i].name = candidates[tmp_position].name;
            // Step 3c: Reassign current candidate to former largest.
            candidates[tmp_position].votes = temp[0].votes;
            candidates[tmp_position].name = temp[0].name;
        }
    }

    // Print all candidates that have highest votes.
    for (int i = 0; i < candidate_count; i++)
    {
        // Solve for ties by looping through the candidates.
        if (candidates[i].votes == candidates[0].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
