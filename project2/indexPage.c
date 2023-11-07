/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

/* TODO: structure definitions */
struct trieNode
{
  char letter;
  int occurences;
  int subCount;
  struct trieNode **subNodes;
};

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
struct trieNode *indexPage(const char *url);

int addWordOccurrence(const char *word, const int wordLength, struct trieNode *root);

void printTrieContents(char *word, struct trieNode *root);

int freeTrieMemory(struct trieNode *node);

int getText(const char *srcAddr, char *buffer, const int bufSize);

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "Missing the file name. \n");
    return -1;
  }

  struct trieNode *root = indexPage(argv[1]);
  printTrieContents(&(root->letter), root);
  freeTrieMemory(root);

  return 0;
}

struct trieNode *createNode(char letter)
{
  struct trieNode *newNode = malloc(sizeof(struct trieNode));
  newNode->letter = letter;
  newNode->occurences = 0;
  newNode->subCount = 0;
  newNode->subNodes = malloc(sizeof(struct trieNode) * 26);
  return newNode;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
struct trieNode *indexPage(const char *url)
{
  
  char buffer[MAX_LEN] = {};
  getText(url, buffer, MAX_LEN);

  printf("%s\n", url);

  int isValid, i, size;

  struct trieNode *root = createNode('\0');

  isValid = 0;
  char *current = buffer;
  size = strlen(buffer);

  for (i = 0; i < size; i++)
  {

    if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z'))
    {
      // changing to lower case if necessary
      if (buffer[i] < 97)
      {
        buffer[i] = (char)buffer[i] + 32;
      }
      isValid = 1;
    }
    else
    {
      if (isValid)
      {
        // null char ends each word at each non-alphabetic char
        buffer[i] = '\0';
        addWordOccurrence(current, strlen(current), root);
        printf("\t%s\n", current);
        isValid = 0;
      }
      current = buffer + i + 1;
    }
  }
  return root;
}

int addWordOccurrence(const char *word, const int wordLength, struct trieNode *root)
{
  int status = -1;
  int nextIndex; // determines which node is the next root

  // checks if current character is in a subnode of the root
  for (int i = 0; i < root->subCount; i++)
  {
    if (*word == root->subNodes[i]->letter)
    {
      status = i;
    }
  }

  if (status != -1)
  { // if the character already has a node, increment occurrences
    if (wordLength == 1)
    {
      root->subNodes[status]->occurences++;
    }
    nextIndex = status;
  }
  else
  { // if the character is not found, make a new subNode
    nextIndex = root->subCount;
    root->subNodes[nextIndex] = createNode(*word);

    // If it's the end of a word, increment occurrences

    if (wordLength == 1)
    {
      root->subNodes[nextIndex]->occurences = 1;
    }
    else
    {
      root->subNodes[nextIndex]->occurences = 0;
    }
    // Number of nodes in root increases
    root->subCount++;
  }

  if (wordLength > 1)
  { // runs until entire word is entered
    word = word + 1;
    addWordOccurrence(word, wordLength - 1, root->subNodes[nextIndex]);
  }
  return 0;
}

void printTrieContents(char *word, struct trieNode *root)
{
  if (root->occurences > 0)
  {
    printf("%s%c: %d\n", (char *)word, (char)root->letter, root->occurences);
  }

  if (root->subCount != 0)
  {
    // Alphabetic sorting
    struct trieNode *sortedNodes[root->subCount];
    //copy memory to maintain structure of orginial trie
    memcpy(sortedNodes, root->subNodes, root->subCount * sizeof(struct trieNode *));

    for (int i = 0; i < root->subCount - 1; ++i)
    {
      for (int j = i + 1; j < root->subCount; ++j)
      {
        if (sortedNodes[i]->letter > sortedNodes[j]->letter)
        {
          struct trieNode *temp = sortedNodes[i];
          sortedNodes[i] = sortedNodes[j];
          sortedNodes[j] = temp;
        }
      }
    }

    char *temp = malloc(strlen(word) + 2);
    strcpy(temp, word);
    temp[strlen(word)] = root->letter;
    temp[strlen(word) + 1] = '\0';

    for (int i = 0; i < root->subCount; ++i)
    {
      printTrieContents(temp, sortedNodes[i]);
    }
    free(temp);
  }
}

int freeTrieMemory(struct trieNode *node)
{
  for (int i = 0; i < node->subCount; ++i)
  {
    freeTrieMemory(node->subNodes[i]);
  }
  free(node->subNodes);
  free(node);
  return 1;
}

/* You should not need to modify this function */
int getText(const char *srcAddr, char *buffer, const int bufSize)
{
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if (pipe == NULL)
  {
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
            buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize - 1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}