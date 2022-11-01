#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letterCount = count_letters(text);
    int wordCount = count_words(text);
    int sentenceCount = count_sentences(text);

    float L = 100.0 * letterCount / wordCount;
    float S = 100.0 * sentenceCount / wordCount;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

int count_letters(string text)
{
    int counter = 0;
    int len = strlen(text);

    for (int i = 0; i < len; ++i)
    {
        if (isalpha(text[i]))
        {
            ++counter;
        }
    }

    return counter;
}

int count_words(string text)
{
    int counter = 0;
    int len = strlen(text);

    for (int i = 0; i < len; ++i)
    {
        if (isspace(text[i]))
        {
            ++counter;
        }
    }

    // Count last word in the sentence
    ++counter;

    return counter;
}

int count_sentences(string text)
{
    int counter = 0;
    int len = strlen(text);

    for (int i = 0; i < len; ++i)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            ++counter;
        }
    }

    return counter;
}
