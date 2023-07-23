// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Using typedef to create 8bit and 16bit data types
typedef uint8_t BIT8;
typedef int16_t BIT16;

// The function prototypes
void copy_header(FILE *input, FILE *output);
void read_samples(FILE *input, FILE *output, float vol_factor);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    copy_header(input, output);

    // Read samples from input file and write updated data to output file
    read_samples(input, output, factor);

    // Close files
    fclose(input);
    fclose(output);
}

// Additional functions

// Function to copy header values from the input file to the output file
void copy_header(FILE *input, FILE *output)
{
    BIT8 header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
}

// Read samples from input files into the output file and modify each sample to change volume.
void read_samples(FILE *input, FILE *output, float vol_factor)
{
    BIT16 buffer;
    while (fread(&buffer, sizeof(BIT16), 1, input))
    {
        buffer *= vol_factor;
        fwrite(&buffer, sizeof(BIT16), 1, output);
    }
}