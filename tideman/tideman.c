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
bool verify_cycle(int winner, int loser);
int creates_cycle(int loser, int winner);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].loser = j;
                pairs[pair_count].winner = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs (Bubble sort) in decreasing order by strength of victory
void sort_pairs(void)
{
    // Temporary pair to keep the smaller strength of victory
    pair temp;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                // Save the smaller one
                temp.winner = pairs[i].winner;
                temp.loser = pairs[i].loser;

                // Change position (j -> i) stronger comes first
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                // Change position (i -> j)
                pairs[j].winner = temp.winner;
                pairs[j].loser = temp.loser;
            }
        }
    }
    for (int k = 0; k < pair_count; k++)
    {
        printf("%s\n%s\n", candidates[pairs[k].winner], candidates[pairs[k].loser]);
        printf("\n");
    }
    return;
}


// Check if there is a cycle
int creates_cycle(int loser, int winner)
{
    int edge_counter = 0;
    int loser1;
    // End condition
    if (locked[loser][winner] == true)
    {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            edge_counter++;
            loser1 = i;
            if (edge_counter == 2)
            {
                return 1;
            }
        }
    }
    if (edge_counter == 1)
    {
        return creates_cycle(loser1, winner);
    }
    return 0;
}

// Checks if the loser is a winner in any other pair
bool verify_cycle(int winner, int loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (creates_cycle(loser, winner))
            {
                return true;
            }
        }
    }
    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // The firsrt one starts being the source
        if (i == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else if (!verify_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    int winner[pair_count];
    int index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false && j == candidate_count - 1)
            {
                winner[index] = i;
                index++;
            }
            else if (locked[j][i] == true)
            {
                break;
            }
        }
    }
    for (int k = 0; k < index; k++)
    {
        printf("%s\n", candidates[winner[k]]);
    }
    return;
}