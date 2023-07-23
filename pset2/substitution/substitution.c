#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string cipher(string text, string KEY);

int key_verification(string KEY);

int main(int argc, string argv[])
{
    // Print error message if no or too many command line arguments specified
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // Get the key from the command line arguments
    string KEY = argv[1];
    
    // pass key into key_verification() function to see if its legit
    int key_genuine = key_verification(KEY);
    
    // If key is not genuine, print error text and return 1
    if (key_genuine == 0)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // Get the plaintext as input
    string text = get_string("plaintext: ");

    
    // Create a cipher using the cipher() function 
    string ciphertext = cipher(text, KEY);
    
    // Print out the ciphertext
    printf("ciphertext: %s\n", ciphertext);
    
    // Return 0 as the exit status
    return 0;
}

string cipher(string text, string KEY)
{
    // Iterate through every character in the text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // If the character is an alphabet, replace the character with a character from the key
        // Also, the new character must be upper or lower according to the replaced one
        if isalpha(text[i])
        {
            if islower(text[i])
            {
                text[i] = tolower(KEY[text[i] - 97]);
            }
            else
            {
                text[i] = toupper(KEY[text[i] - 65]);
            }
        }
    }
    // Return the modified text
    return text;
}


int key_verification(string KEY)
{
    // n is the length of the KEY
    int n = strlen(KEY);
    
    // If the length of the key dosen't equal 24, return 0
    if (n != 26)
    {
        return 0;
    }
    
    // Iterate through every character in the key
    for (int i = 0; i < n; i++)
    {
        // If any character isn't an alphabet, return 0
        if (! isalpha(KEY[i]))
        {
            return 0;
        }
        
        // If any alphabet is repeated in the key, return 0
        for (int j = 0; j < n; j++)
        {
            if (i != j && KEY[i] == KEY[j])
            {
                return 0;
            }
        }
    }
    
    // If the key has no problems, return 1
    return 1;
}