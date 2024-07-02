#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string phrase = get_string("Enter a phrase: ");

    for (int i = 0, lenght = strlen(phrase); i < lenght - 1; i++)
    {
        //check if char arent alphabetical
        if(phrase[i] > phrase[i + 1])
        {
            printf("Not in alphabetical order.\n");
            return 0;
        }
    }
    printf("It's in alphabetical order.\n");
        return 0;
}
