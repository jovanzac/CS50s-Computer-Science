#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start_size;
    do 
    {
        start_size = get_int("Please input the start size: "); 
    }
    while (start_size < 9);

    // Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("Please input the end size: "); 
    }
    while (end_size < start_size);

    // Calculating number of years until we reach threshold
    int year_end_size = start_size;
    int years = 0;
    while (year_end_size < end_size)
    {
        // size at the end of the year = current size + number llamas born - number llamas dead
        year_end_size += (year_end_size / 3 - year_end_size / 4);
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}