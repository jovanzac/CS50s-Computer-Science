#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asking for User's name and welcoming them
    string name = get_string("What is your name? ");
    printf("Hello, %s\n", name);
}