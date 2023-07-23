#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Printing the winner
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
    // Computing and returning the score for given string
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Converting the character at the i^th index of the string to lowercase
        char lowercase_char = tolower(word[i]);
        // If the character is an alphabet then add the corresponding point to score
        if (lowercase_char >= 97 && lowercase_char <= 122)
        {
            score += POINTS[lowercase_char - 97];
        }
    }
    // Return final score
    return score;
}