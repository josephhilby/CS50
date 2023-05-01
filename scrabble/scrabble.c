#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[]   = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char LETTERS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// Define table size to use in object creation
#define TABLE_SIZE 26

// Create an object to use as a key/value pair in a hash
typedef struct
{
    char letter;
    int score;
} letterScore;

// Creat a hash table
letterScore hashTable[TABLE_SIZE];

// Hash the key to return the index position of the object
unsigned int hash(char letter)
{
    int hashReturn = (int) letter % TABLE_SIZE;
    return hashReturn;
}

// Function names
int compute_score(string word);
void initHashTable();
string downcase(string word);
int findCharValue(char c);

// For debugging
void printTable();

int main(void)
{
    initHashTable();

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Downcase the words
    string downcaseWord1 = downcase(word1);
    string downcaseWord2 = downcase(word2);

    // Score both words
    int score1 = compute_score(downcaseWord1);
    int score2 = compute_score(downcaseWord2);

    // Return results
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Downcase string
string downcase(string word)
{
    int n = strlen(word);
    string downcaseWord = word;
    for (int i = 0; i < n; i++)
    {
        downcaseWord[i] = tolower(word[i]);
    }
    return downcaseWord;
}

// Score downcased string
int compute_score(string word)
{
    int score = 0;
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        score += findCharValue(word[i]);
    }
    return score;
}

// Determine the value of each char in the string and remove any non-alpha
int findCharValue(char c)
{
    if (isalpha(c) != 0)
    {
        int i = hash(c);
        return hashTable[i].score;
    }
    else
    {
        return 0;
    }
}

// Initialize hash and populate it with key value pairs
void initHashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        letterScore ls = {.letter = LETTERS[i], .score = POINTS[i]};
        int index = hash(ls.letter);
        hashTable[index] = ls;
    }
}

// Print hash (for debugging only)
void printTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        char key = hashTable[i].letter;
        int value = hashTable[i].score;
        int hashTableIndex = hash(key);
        printf("\t%i\t%i\t%c\t%i\n", i, hashTableIndex, key, value);
    }
}
