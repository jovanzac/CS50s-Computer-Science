#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int get_letters(string text);

int get_words(string text);

int get_sentences(string text);

int main(void)
{
    // Accept a text as input
    string text = get_string("Text: ");
    
    // Get number of letters, words and sentences in the text
    int letters = get_letters(text);
    int words = get_words(text);
    int sentences = get_sentences(text);
    
    // L --> number of letters per 100 words
    float L = (letters / (float) words) * 100;
    // S --> number of words per 100 sentences
    float S = (sentences / (float) words) * 100;
    
    // Calculating the grade of the text using the Coleman Liau index
    int coleman_liau_index = round((0.0588 * L) - (0.296 * S) - 15.8);
    
    // Printing the text's grade
    if (coleman_liau_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_liau_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", coleman_liau_index);
    }
}

int get_letters(string text)
{
    // Letters keeps count of number of letters in the text
    int letters = 0;
    // Iterating through each character in the text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char lowercase_char = tolower(text[i]);
        // checking whether a character is a letter and if true, adding 1 to letters
        if (lowercase_char >= 97 && lowercase_char <= 122)
        {
            letters++;
        }
    }
    return letters;
}

int get_words(string text)
{
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words ++;
        }
    }
    return words;
}

int get_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}