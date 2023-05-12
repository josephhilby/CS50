// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node table[N];

// Hash table LL tails
node *tails[N];

// Length of given word
int wordLength;

// Number of words loaded
int words;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  wordLength = strlen(word);
  int size = wordLength + 1;
  char *downcased = malloc(size);
  if (downcased == NULL)
  {
    return false;
  }

  for (int i = 0; i < size; i++)
  {
    downcased[i] = tolower(word[i]);
  }

  int index = hash(downcased);

  node *temp;
  temp = &table[index];

  if (temp->word[0] != 0)
  {
    do
    {
      if (strcmp(temp->word, downcased) == 0)
      {
        free(downcased);
        return true;
      }
      temp = temp->next;
    } while (temp != NULL);
  }

  free(downcased);
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  int sum = 0;
  for (int i = 0; i < wordLength; i++)
  {
    sum += word[i];
  }
  return sum % N;
}

static void input_word(const char *word)
{
  int index = hash(word);

  if (table[index].word[0] == 0)
  {
    for (int i = 0; i < wordLength; i++)
    {
      table[index].word[i] = word[i];
    }
    table[index].next = NULL;
    tails[index] = &table[index];
  }
  else
  {
    node *temp = malloc(sizeof(node));
    if (temp == NULL)
    {
      return;
    }
    for (int i = 0; i < wordLength; i++)
    {
      temp->word[i] = word[i];
    }
    temp->next = NULL;
    tails[index]->next = temp;
    tails[index] = temp;
  }
  words++;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
  // Open the dictionary
  FILE *file = fopen(dictionary, "r");
  if (file == NULL)
  {
    printf("Could not open %s.\n", dictionary);
    unload();
    return false;
  }

  int index = 0;
  char word[LENGTH + 1];

  char c;
  while (fread(&c, sizeof(char), 1, file))
  {
    if (isalpha(c) || (c == '\'' && index > 0))
    {
      word[index] = c;
      index++;

      if (index > LENGTH)
      {
        while (fread(&c, sizeof(char), 1, file) && isalpha(c))
          ;
        index = 0;
      }
    }
    else if (isdigit(c))
    {
      while (fread(&c, sizeof(char), 1, file) && isalnum(c))
        ;
      index = 0;
    }
    else if (index > 0)
    {
      word[index] = '\0';
      wordLength = index;
      input_word(word);
      index = 0;
    }
  }
  fclose(file);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  return words;
}

void free_index(node *n)
{
  if (n == NULL)
  {
    return;
  }
  else if (n->next != NULL)
  {
    free_index(n->next);
  }
  free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  for (int i = 0; i < N; i++)
  {
    if (table[i].next != NULL)
    {
      free_index(table[i].next);
    }
  }
  return true;
}
