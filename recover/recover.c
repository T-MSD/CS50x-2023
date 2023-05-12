#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    // open file
    FILE *file = fopen(argv[1], "r");
    // Check if the files was opened
    if (file == NULL)
    {
        printf("Can't open the file");
        return 1;
    }

    // Initialize variables
    int counter = 0;
    BYTE buffer[BLOCK_SIZE];
    FILE *new_image = NULL;
    char *name = malloc(8 * sizeof(char));

    // Repeat until the end
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // New jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // First jpeg
            if (counter == 0)
            {
                sprintf(name, "%03d.jpg", counter);
                new_image = fopen(name, "w");
                fwrite(buffer, 1, BLOCK_SIZE, new_image);
            }
            // If its not the first one
            else
            {
                fclose(new_image);
                sprintf(name, "%03d.jpg", counter);
                new_image = fopen(name, "w");
                fwrite(buffer, 1, BLOCK_SIZE, new_image);
            }
            counter++;
        }
        // Jpeg already found
        else if (new_image != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, new_image);
        }
    }

    // Close files
    fclose(new_image);
    free(name);
    fclose(file);
}