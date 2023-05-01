#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Globals
#define TABLE_SIZE 26
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char encoded[128] = "";

// Hash
typedef struct
{
    char letter;
    char encodedLetter;
} letterScore;

letterScore hashTable[TABLE_SIZE];

//Helper Functions
unsigned int hash(char letter);
int initHashTable(string cypher);
void printTable();
int checkKey(string key[], int argc);
void encode_string(string plaintext);

int main(int argc, string argv[])
{
    // Collect key from user argv[1]
    // Check if string contains all 26 chars and no duplicates / missing chars
    // Downcase string
    if (checkKey(argv, argc) == 1)
    {
        return 1;
    }

    // Init hash table with string
    if (initHashTable(argv[1]) == 1)
    {
        return 1;
    }

    // Collect plaintext from user
    // Downcase plane text but keep case for encoding
    string plaintext = get_string("plaintext: ");
    encode_string(plaintext);

    // Encode plaintext return with case preserved
    printf("ciphertext: %s\n", encoded);
}

unsigned int hash(char letter)
{
    int hashReturn = (int) letter % TABLE_SIZE;
    return hashReturn;
}

// Initialize hash and populate it with key value pairs
int initHashTable(string cypher)
{
    int count[TABLE_SIZE] = {0};
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        char upcaseCypher = toupper(cypher[i]);
        letterScore ls = {.letter = letters[i], .encodedLetter = upcaseCypher};
        int index = hash(ls.letter);
        int countIndex = hash(ls.encodedLetter);
        count[countIndex]++;
        if (count[countIndex] > 1)
        {
            printf("All 26 characters in key must be unique alphabetic characters.\n");
            return 1;
        }
        hashTable[index] = ls;
    }
    return 0;
}

int checkKey(string key[], int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(key[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(key[1][i]) == 0)
            {
                printf("All 26 characters in key must be alphabetic characters.\n");
                return 1;
            }
        }
        return 0;
    }
}

void encode_string(string plaintext)
{
    int N = strlen(plaintext);
    for (int i = 0; i < N; i++)
    {
        char key = plaintext[i];
        if (isalpha(key) != 0)
        {
            char encodedChar = hashTable[hash(tolower(key))].encodedLetter;
            if (islower(key) != 0)
            {
                encodedChar = tolower(encodedChar);
            }
            strncat(encoded, &encodedChar, 1);
        }
        else
        {
            strncat(encoded, &key, 1);
        }
    }
}

// For debuging only
void printTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        char key = hashTable[i].letter;
        char value = hashTable[i].encodedLetter;
        int hashTableIndex = hash(key);
        printf("\t%i\t%i\t%c\t%c\n", i, hashTableIndex, key, value);
    }
}