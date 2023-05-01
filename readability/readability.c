#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//Helper Functions
void analyze_text(string text, int N);
float avg_sentence_count();
float avg_letter_count();
int compute_grade_level(int L, int S);

// Globals
int letterCount;
int wordCount;
int sentenceCount;

int main(void)
{
    letterCount = 0;
    wordCount = 1;
    sentenceCount = 0;

    // Get string from user ("Text: ")
    string text = get_string("Text: ");

    // Get string length (strlen)
    int N = strlen(text);

    // Count the number of letters (a-z & A-Z)
    // Count the number of words (spaces)
    // Count the number of sentences (. ? ! ;)
    analyze_text(text, N);
    printf("Letter Count: %i\n", letterCount);
    printf("Word Count: %i\n", wordCount);
    printf("Sentence Count: %i\n", sentenceCount);

    // Reason out how many letters and sentences would exist with 100 words
    // (<letter count> / <word count>) * 100 = L
    float letterAvgCount100 = avg_letter_count();
    // (<sentence count> / <word count>) * 100 = S
    float sentenceAvgCount100 = avg_sentence_count();

    // Compute the grade level
    // 0.0588 * L - 0.296 * S - 15.8 = grade
    int gradeLevel = compute_grade_level(letterAvgCount100, sentenceAvgCount100);

    // Return the result "Grade %i\n"
    printf("Grade %i\n", gradeLevel);
}

// Iterate throught the string and count:
// letters (isalpha),
// spaces between words (isspace),
// and sentences (. ! ? ;) (!isalnum && !isspace)
void analyze_text(string text, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (isalpha(text[i]))
        {
            letterCount++;
        }
        if (isspace(text[i]))
        {
            wordCount++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount++;
        }
    }
}

float avg_letter_count()
{
     return ((float) letterCount / wordCount) * 100;
}

float avg_sentence_count()
{
    return ((float) sentenceCount / wordCount) * 100;
}

// Use Coleman-Liau index
int compute_grade_level(int L, int S)
{
    return 0.0588 * L - 0.296 * S - 15.8;
}