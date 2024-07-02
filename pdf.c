#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, string argv[])
{
    // Check first four bytes in given file
    if (argc != 2)
    {
        return 1;
    }

    const int n = 4;
    string filename = argv[1];
    FILE *f = fopen(filename, "r");
    BYTE buffer[n];
    fread(buffer, 1, n, f);

    for (int i = 0; i < n; i++)
    {
        printf("%i\n", buffer[i]);
    }
    fclose(f);
}
