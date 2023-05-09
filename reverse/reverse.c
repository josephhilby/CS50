#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Set HEADER_SIZE
    const int HEADER_SIZE = sizeof(WAVHEADER);

    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: reverse [input.wav] [output.wav]\n");
        return 1;
    }

    // Create filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file for reading
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Read infile's header
    WAVHEADER wh;
    fread(&wh, HEADER_SIZE, 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(wh) != 0)
    {
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 1;
    }

    // Open output file for writing
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 1;
    }

    // Write header to file
    fwrite(&wh, HEADER_SIZE, 1, outptr);

    // Use get_block_size to calculate size of block (in bytes)
    int block = get_block_size(wh);

    // Set asside memory to write in
    BYTE *buffer;

    // Move to the end of the file in prep for writing in reverse
    fseek(inptr, block, SEEK_END);

    // Write reversed audio to outfile with for loop
    long fileSize = ftell(inptr);
    for (long i = fileSize; i > HEADER_SIZE; i -= block)
    {
        // Reset the pointer
        fseek(inptr, i, SEEK_SET);

        // Read and write the blocks
        fread(&buffer, block, 1, inptr);
        fwrite(&buffer, block, 1, outptr);
    }

    // // Write reversed audio to outfile with while loop (found this solution while troubleshooting my for loop)
    // while(ftell(inptr) - block > HEADER_SIZE)
    // {
    //     // Reset the pointer two blocks (the on you read and the one you will read)
    //     fseek(inptr, -2 * block, SEEK_CUR);

    //     // Read and write the blocks
    //     fread(&buffer, block, 1, inptr);
    //     fwrite(&buffer, block, 1, outptr);
    // }

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}

int check_format(WAVHEADER header)
{
    if
    (
        header.format[0] == 'W' &&
        header.format[1] == 'A' &&
        header.format[2] == 'V' &&
        header.format[3] == 'E'
    )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    // size of each block == number of channels multiplied by bytes per sample.
    int blockSize = header.numChannels * (header.bitsPerSample / 8);
    return blockSize;
}