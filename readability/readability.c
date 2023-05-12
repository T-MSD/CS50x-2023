#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void count(string text);
void Coleman_Liau(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    count(text);
}


// Counts the number of words, letters and sentences
void count(string text)
{
    int count_letters = 0;
    int count_words = 0;
    int count_sentences = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        // Only counts alphabetic characters
        if (isalpha(text[i]))
        {
            count_letters++;
        }
    }

    // Counts words
    for (int j = 0; j < length; j++)
    {
        // This avoids counting extra words after a sentence
        if (text[j] == ' ' && (text[j - 1] == '.' || text[j - 1] == ',' || text[j - 1] == '!' || text[j - 1] == '?'))
        {
            count_words += 0;
        }
        else if (text[j] == ' ' || text[j] == '.' || text[j] == ',' || text[j] == '!' || text[j] == '?')
        {
            count_words++;
        }
    }

    // Counts sentences
    for (int k = 0; k < length; k++)
    {
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            count_sentences++;
        }
    }

    Coleman_Liau(count_letters, count_words, count_sentences);
}


// Coleman-Liau Formula
void Coleman_Liau(int letters, int words, int sentences)
{
    double L = letters * 100 / (float) words;
    double S = sentences * 100 / (float) words;
    // Formula
    double index = (0.0588 * L) - (0.296 * S) - 15.8;
    // Round
    index = round(index);
    int grade = index;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 16 && index > 1)
    {
        printf("Grade %d\n", grade);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
}