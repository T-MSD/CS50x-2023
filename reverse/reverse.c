#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *fd = fopen(argv[1], "r");
    if (fd == NULL)
    {
        printf("Error opening %s\n", argv[1]);
        return 1;
    }

    // Read header into an array
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, fd);


    // Use check_format to ensure WAV format
    if (check_format(header) != 0)
    {
        fclose(fd);
        return 1;
    }

    // Open output file for writing
    FILE *out_fd = fopen(argv[2], "w");
    if (out_fd == NULL)
    {
        printf("Error opening %s\n", argv[2]);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, out_fd);
    int header_end = ftell(out_fd);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE audiobuff[block_size];
    int offset = -2 * block_size;
    fseek(fd, -block_size, SEEK_END);
    int cur;

    do
    {
        fread(audiobuff, block_size, 1, fd);
        fwrite(audiobuff, block_size, 1, out_fd);
        fseek(fd, offset, SEEK_CUR);
        cur = ftell(fd);
    }
    while (cur != header_end - block_size);

    fclose(fd);
    fclose(out_fd);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return header.numChannels * (header.bitsPerSample / 8);
}