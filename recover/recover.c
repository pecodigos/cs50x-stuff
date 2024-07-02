#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

const int BLOCKSIZE = 512;
const int FILENAMESIZE = 9;

int main(int argc, char *argv[])
{
    // Accept only a single command-line argument
    if (argc != 2)
    {
        printf("Usage ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Failed to open the file\n");
        return 2;
    }

    // Create a buffer
    BYTE buffer[BLOCKSIZE];

    // Keeping track of each JPEF file, starting at 0
    int jpegnum = 0;
    char recoveredfile[FILENAMESIZE];

    // Boolean for if new JPEG is find
    bool fileIsOpen = false;

    // Img file declared outside of while loop
    FILE *img;

    // Read the data until there's no longer any data left
    while (fread(buffer, 1, BLOCKSIZE, card) == BLOCKSIZE)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Create JPEG files from the data
            if (fileIsOpen == true)
            {
                fclose(img);
                fileIsOpen = false;
            }
            sprintf(recoveredfile, "%03i.jpg", jpegnum);
            img = fopen(recoveredfile, "w");
            fwrite(buffer, 1, BLOCKSIZE, img);
            if (img != NULL)
            {
                fileIsOpen = true;
            }
            jpegnum++;
        }
        else if (fileIsOpen == true)
        {
            fwrite(buffer, 1, BLOCKSIZE, img);
        }
    }
    if (fileIsOpen == true)
    {
        fclose(img);
        fileIsOpen = false;
    }
    fclose(card);
}
