#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compares scores and prints the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Compute and return score for string

    int length = strlen(word);
    int points = 0;

    // word[i] = each character
    for (int i = 0; i < length; i++)
    {
        // Sums the points of each letter
        if (toupper(word[i]) == 'A' || toupper(word[i]) == 'E' || toupper(word[i]) == 'I' || toupper(word[i]) == 'L' ||
            toupper(word[i]) == 'N' || toupper(word[i]) == 'O' || toupper(word[i]) == 'R' || toupper(word[i]) == 'S' ||
            toupper(word[i]) == 'T' || toupper(word[i]) == 'U')
        {
            points++;
        }
        else if (toupper(word[i]) == 'D' || toupper(word[i]) == 'G')
        {
            points += 2;
        }
        else if (toupper(word[i]) == 'B' || toupper(word[i]) == 'C' || toupper(word[i]) == 'M' || toupper(word[i]) == 'P')
        {
            points += 3;
        }
        else if (toupper(word[i]) == 'F' || toupper(word[i]) == 'H' || toupper(word[i]) == 'V' || toupper(word[i]) == 'W'
                 || toupper(word[i]) == 'Y')
        {
            points += 4;
        }
        else if (toupper(word[i]) == 'K')
        {
            points += 5;
        }
        else if (toupper(word[i]) == 'J' || toupper(word[i]) == 'X')
        {
            points += 8;
        }
        else if (toupper(word[i]) == 'Q' || toupper(word[i]) == 'Z')
        {
            points += 10;
        }
        // Characters that are not letters
        else
        {
            points += 0;
        }
    }
    return points;

}
