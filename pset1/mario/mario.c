#include <stdio.h>
#include <cs50.h>

void pyramids(int rows);

int get_rows(void);

int main(void)
{
    // Get the number of rows the block should have
    int rows = get_rows();

    // Print pyraminds according to the value of rows
    pyramids(rows);
}

void pyramids(int rows)
{
    // Iterate rows times to print the rows of both pyramids
    for (int i = 1; i < rows + 1; i++)
    {
        // Iterate rows times to print i blocks in each pyramid in every row
        for (int j = 1; j < rows + i + 1; j++)
        {
            if (j <= rows - i || j > rows + i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
            if (j == rows)
            {
                printf("  ");
            }
        }
        // \n to separate each row
        printf("\n");
    }
}

int get_rows(void)
{
    // Accept number of rows to use as input and return it
    int rows;
    do
    {
        rows = get_int("How many rows do you want? ");
    }
    while (rows < 1 || rows > 8);
    return rows;
}