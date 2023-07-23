#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        int top_valid_rank = 0;
        // If top candidate is already eliminated
        if (candidates[preferences[i][top_valid_rank]].eliminated)
        {
            // Loop over the remaining candidates ignoring the voter's top preference
            for (int j = top_valid_rank + 1; j < candidate_count; j++)
            {
                // If this candidate is not yet eliminated, they become the voter's valid top preference
                if (!candidates[preferences[i][j]].eliminated)
                {
                    top_valid_rank = j;
                    break;
                }
            }
        }
        // Set the top preference as the candidate at rank can
        int top_candidate = preferences[i][top_valid_rank];
        // Increment the number of votes this candidate has
        candidates[top_candidate].votes++;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initializing variable min_vote which will later store the least votes recieved by any candidate
    int min_vote_counter = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min_vote_counter && !candidates[i].eliminated)
        {
            min_vote_counter = candidates[i].votes;
        }
    }
    return min_vote_counter;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int temp_vote;
    int counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // Initialize the value of votes. It will be used to check if the other valid candidates have the same number of votes
        if (!candidates[i].eliminated)
        {
            temp_vote = candidates[i].votes;
            break;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // If the votes of any candidate does not equal the initialized value and the candidate is not yet eliminated return false
        if ((candidates[i].votes != temp_vote) && !candidates[i].eliminated)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == min) && (!candidates[i].eliminated))
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}