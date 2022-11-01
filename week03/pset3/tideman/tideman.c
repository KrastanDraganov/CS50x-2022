#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

int preferences[MAX][MAX];

bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
}
pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool vote(int rank, string vote_name, int ranks[]);
void record_preferences(int ranks[]);

void add_pairs(void);
void sort_pairs(void);

bool is_cycle(int current_candidate, int starting_candidate);
void lock_pairs(void);

void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; ++i)
    {
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; ++i)
    {
        for (int j = 0; j < candidate_count; ++j)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; ++i)
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; ++j)
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

bool vote(int rank, string vote_name, int ranks[])
{
    for (int i = 0; i < candidate_count; ++i)
    {
        if (strcmp(candidates[i], vote_name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; ++i)
    {
        for (int j = i + 1; j < candidate_count; ++j)
        {
            int winner = ranks[i];
            int loser = ranks[j];

            ++preferences[winner][loser];
        }
    }

    return;
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; ++i)
    {
        for (int j = i + 1; j < candidate_count; ++j)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                ++pair_count;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                ++pair_count;
            }
        }
    }

    return;
}

void sort_pairs(void)
{
    for (int i = pair_count - 1; i >= 0; --i)
    {
        bool is_swap = false;

        for (int j = pair_count - 1; j >= pair_count - i; --j)
        {
            int votes1 = preferences[pairs[j].winner][pairs[j].loser];
            int votes2 = preferences[pairs[j - 1].winner][pairs[j - 1].loser];

            if (votes1 > votes2)
            {
                is_swap = true;

                pair current_pair = pairs[j];
                pairs[j] = pairs[j - 1];
                pairs[j - 1] = current_pair;
            }
        }

        if (!is_swap)
        {
            break;
        }
    }

    return;
}

bool is_cycle(int current_candidate, int starting_candidate)
{
    if (current_candidate == starting_candidate)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; ++i)
    {
        if (!locked[current_candidate][i])
        {
            continue;
        }

        if (is_cycle(i, starting_candidate))
        {
            return true;
        }
    }

    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; ++i)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (is_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; ++i)
    {
        bool is_edge_in = false;

        for (int j = 0; j < candidate_count; ++j)
        {
            if (locked[j][i])
            {
                is_edge_in = true;
                break;
            }
        }

        if (!is_edge_in)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}
