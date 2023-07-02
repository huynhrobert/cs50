#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool will_create_cycle(int start, int end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // Loop through each candidate and check match on name.
    for (int i = 0; i < candidate_count; i++)
    {
        // https://manual.cs50.io/3/strcmp
        if (strcmp(candidates[i], name) == 0)
        {
            // If it's a match, assign a rank to the candidate.
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // Go through and record for each candidate i.
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare against all candidates ranked lower.
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Record a win against each candidate.
            preferences[ranks[i]][ranks[j]]++;
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Go through each combination for i and j preferences.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If not a tie, record outcome.
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Selection sort pairs by strength of win, descending order.
    // Step 1: Loop from 0 to N - 1.
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Step 2: Find largest number between i and i - 1.
        int tmp_position = pair_count - 1;
        for (int j = i; j < pair_count - i - 1; j++)
        {
            if (
                // Strength of current position i.
                (float)preferences[pairs[j].winner][pairs[j].loser] /
                (float)preferences[pairs[j].loser][pairs[j].winner]
                >
                // Strength of temporary position.
                (float)preferences[pairs[tmp_position].winner][pairs[tmp_position].loser] /
                (float)preferences[pairs[tmp_position].loser][pairs[tmp_position].winner])
            {
                tmp_position = j;
            }
        }
        // Step 3: Swap the largest number with i.
        if (
            // Position of largest number.
            (float)preferences[pairs[tmp_position].winner][pairs[tmp_position].loser]
            /
            (float)preferences[pairs[tmp_position].loser][pairs[tmp_position].winner]
            >
            // Position of current number i.
            (float)preferences[pairs[i].winner][pairs[i].loser]
            /
            (float)preferences[pairs[i].loser][pairs[i].winner])
        {
            pair temp[1];
            // Step 3a: Store current pair info.
            temp[0].winner = pairs[i].winner;
            temp[0].loser  = pairs[i].loser;
            // Step 3b: Assign largest to current pair.
            pairs[i].winner = pairs[tmp_position].winner;
            pairs[i].loser = pairs[tmp_position].loser;
            // Step 3c: Reassign current pair to former largest.
            pairs[tmp_position].winner = temp[0].winner;
            pairs[tmp_position].loser = temp[0].loser;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // Lock pairs based on descending sort and skip if it'll create a cycle.
    for (int i = 0; i < pair_count; i++)
    {
        // Check if a cycle is created.
        if (!will_create_cycle(pairs[i].winner, pairs[i].loser))
        {
            // Lock in pair since not cycle was created.
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // The winner is candidate without arrows pointing towards them.
    for (int i = 0; i < candidate_count; i++)
    {
        string src_winner = candidates[i];
        int streak = 0;
        // Loop through to see if candidate i has lost against j.
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if candidate i is on a streak.
            if (locked[j][i] == false)
            {
                streak++;
                // If undefeated, declare as winner.
                if (streak == candidate_count)
                {
                    printf("%s\n", src_winner);
                }
            }
        }
    }
    return;
}

// Check if locking a pair will create a cycle.
bool will_create_cycle(int pair_winner, int pair_loser)
{
    // If the loser has beaten the winner before, it's a cycle.
    if (pair_loser == pair_winner)
    {
        return true;
    }
    // Loop through all candidates i to see if they have any wins.
    for (int i = 0; i < candidate_count; i++)
    {
        // Locked array will swap to true if the loser had any wins.
        if (locked[pair_loser][i])
        {
            // Work backwards from there to see if it ties back to the winner.
            if (will_create_cycle(pair_winner, i))
            {
                return true;
            }
        }
    }
    return false;
}
