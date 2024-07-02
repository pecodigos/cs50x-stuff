#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string text);
char rotate(char c, int k);

int main(int argc, string argv[])
{
    // Test if the program runs with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Test if every character in argv[1] is a digit
    bool digit = only_digits(argv[1]);

    if (digit == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a 'string' to an 'int'
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // For each character in the plaintext:
    int lenght = strlen(plaintext);
    char ciphertext[lenght + 1];

    // Rotate the character if it's a letter
    for (int i = 0; i < lenght; i++)
    {
        ciphertext[i] = rotate(plaintext[i], key);
    }

    ciphertext[lenght] = '\0';

    // Print ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

bool only_digits(string text)
{
    for (int i = 0, lenght = strlen(text); i < lenght; i++)
    {
        if (!isdigit(text[i]))
        {
            return false;
        }
    }
    return true;
}
char rotate(char c, int k)
{
    char pi, ci, character;
    if (isupper(c))
    {
        pi = c - 65;
        ci = (pi + k) % 26;
        character = ci + 65;
    }
    else if (islower(c))
    {
        pi = c - 97;
        ci = (pi + k) % 26;
        character = ci + 97;
    }
    else
    {
        return c;
    }
    return character;
}
