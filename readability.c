#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");
    // Count the number of letter, words, and sentences in the text
    float count1 = count_letters(text);
    float count2 = count_words(text);
    float count3 = count_sentences(text);
    // Coleman-Liau index formula
    float L = (count1 / count2) * 100;
    float S = (count3 / count2) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
int count_letters(string text)
{
    // Return number of letter in text
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
        if (isalpha(text[i]))
        {
            letters++;
        }
    return letters;
}
int count_words(string text)
{
    // Return number of words in text
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
        if (isblank(text[i]))
        {
            words++;
        }
    return words;
}
int count_sentences(string text)
{
    // Return number of sentences in text
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    return sentences;
}
