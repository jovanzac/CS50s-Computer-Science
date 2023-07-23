#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef enum { false, true } bool;

// Initializes the number of bytes a single "block" contains in a FAT file system
const int fat_block_size = 512;
// A counter that keeps track of the jpeg files
int file_counter = 0;

// Prototype of functions
bool jpeg_start(BYTE buffer[]);
FILE *open_jpeg(void);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // Open the raw file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 1;
    }

    // Buffer to store the bytes read from the raw file
    BYTE buffer[fat_block_size];
    // Initialize variable that will contain the jpeg file
    FILE *jpg_file = NULL;
    // While loop
    while (fread(buffer, fat_block_size, 1, raw_file))
    {
        bool is_jpg_start = jpeg_start(buffer);
        if (is_jpg_start)
        {
            // If a jpeg file had already been open, it has reached its end so close it
            if (jpg_file != NULL)
            {
                fclose(jpg_file);
            }
            // Open a new jpeg file
            jpg_file = open_jpeg();
            if (jpg_file == NULL)
            {
                fprintf(stderr, "Could not create JPG number %i.\n", file_counter);
                fclose(raw_file);
                return 2;
            }
        }
        // If a jpeg file exists, write into it
        if (jpg_file != NULL)
        {
            fwrite(buffer, fat_block_size, 1, jpg_file);
        }
    }
    fclose(raw_file);
}

bool jpeg_start(BYTE buffer[])
{
    bool is_jpg_start = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) ? true : false;
    return is_jpg_start;
}

FILE *open_jpeg(void)
{
    char *jpg_name = malloc(8);
    sprintf(jpg_name, "%03i.jpg", file_counter);
    file_counter++;
    FILE *jpg_file = fopen(jpg_name, "w");
    free(jpg_name);
    return jpg_file;
}