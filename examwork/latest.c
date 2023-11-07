/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000 

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

void addWordOccurrence(struct trieNode *root, const char *word);
                     

void printTrieContents(char *word, struct trieNode *root);

int freeTrieMemory(struct trieNode *node);

int main(int argc, char **argv)
{
 if (argc < 2) {
        fprintf(stderr, "Missing the file name. \n");
        return -1;
    }

struct trieNode *root = indexPage(argv[1]);
freeTrieMemory(root);

  return 0;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
struct trieNode *indexPage(const char *url)
{
   // url = getText();
    const char *current = url;

    int isValid, i, size;
    struct trieNode *root = malloc(sizeof(struct trieNode));

    root->letter = '\0';
    root->occurences = 0;
    root->subCount = 0;
    root->subNodes = (struct trieNode **)malloc(sizeof(struct trieNode *) * 26);
    for (i = 0; i < 26; i++)
    {
        root->subNodes[i] = NULL;
    }

    isValid = 0;
    current = url;
    size = strlen(url);

    for (i = 0; i < size; i++)
    {
        if ((url[i] == ' ') || (url[i] == '\n'))
        {
            if (isValid)
            {
                addWordOccurrence(root, current);
                isValid = 0;
            }
            current = url + i + 1;
        }
        else if ((url[i] >= 'A' && url[i] <= 'Z') || (url[i] >= 'a' && url[i] <= 'z'))
        {
            isValid = 1;
        }
    }

    return root;
}

void addWordOccurrence(struct trieNode *root, const char *word)
{
    struct trieNode *current = root;

    for (int i = 0; i < strlen(word); i++)
    {
        char c = word[i];
        int index = c - 'a'; 

        if (current->subNodes[index] == NULL)
        {
            // if the subNode doesnt exist then make a new one
            current->subNodes[index] = (struct trieNode *)malloc(sizeof(struct trieNode));
            current->subNodes[index]->letter = c;
            current->subNodes[index]->occurences = 0;
            current->subNodes[index]->subCount = 0;
            current->subNodes[index]->subNodes = (struct trieNode **)malloc(sizeof(struct trieNode *) * 26);

            for (int j = 0; j < 26; j++)
            {
                current->subNodes[index]->subNodes[j] = NULL;
            }
        }

        current = current->subNodes[index];
    }

    
    current->occurences++;
}

void printTrieContents(char *word, struct trieNode *root)
{
  if (root->subCount != 0)
  {
    char *temp = malloc(sizeof(char) * (strlen(word)));
    strcpy(temp, word);
    temp[strlen(word)] = '\0';
    strcat(temp, (char *)&(root->letter));
    for (int i = 0; i < root->subCount; ++i)
    {
      printTrieContents(temp, root->subNodes[i]);
    }
    free(temp);
  }
  if (root->occurences > 0)
  {
    printf("%s%c: %d\n", (char *)word, (char)root->letter, root->occurences);
  }
}

int freeTrieMemory(struct trieNode *node)
{
  if (node == NULL)
  {
    return 0;
  }
  for (int i = 0; i < 26; i++)
  {
    freeTrieMemory(node->subNodes[i]);
  }
  free(node->subNodes);
  free(node);
  return 1;
}
