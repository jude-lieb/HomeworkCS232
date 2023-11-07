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

int addWordOccurrence(const char* word, const int wordLength, struct trieNode *root);
                     

void printTrieContents(char *word, struct trieNode *root);

int freeTrieMemory(struct trieNode *node);

int getText(const char* srcAddr, char* buffer, const int bufSize);

int main(int argc, char **argv)
{
 if (argc < 2) {
        fprintf(stderr, "Missing the file name. \n");
        return -1;
    }

struct trieNode *root = indexPage(argv[1]);
printTrieContents(&(root -> letter), root);
freeTrieMemory(root);

  return 0;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
struct trieNode *indexPage(const char *url)
{
    char *current;
    char buffer[300000] = {};
    getText(url, buffer, 300000);

    printf("%s\n",url);

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
    current = buffer;
    size = strlen(buffer);

    for (i = 0; i < size; i++)
    {

      if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z'))
      {
        //changing to lower case if necessary
        if(buffer[i] < 97) {
          buffer[i] = (char) buffer[i] + 32;
        }
        isValid = 1;
      } else {
        if (isValid)
        {   
            //null char ends each word at each non-alphabetic char
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

int addWordOccurrence(const char* word, const int wordLength, struct trieNode *root)
{
  int status = -1;
  int nextIndex; //determines which node is the next root

  //checks if current character is in a subnode of the root
  for(int i = 0; i < root -> subCount; ++i) {
    if(*word == root -> subNodes[i] -> letter) {
      status = i;
    }
  }

  if(status != -1) { //if the character already has a node, increment occurrences
    if(wordLength == 1) {
        root -> subNodes[status] -> occurences++;
    }
    nextIndex = status;
  } else { //if the character is not found, make a new subNod
    nextIndex = root -> subCount;
    root -> subNodes[nextIndex] = malloc(sizeof(struct trieNode*));
    root -> subNodes[nextIndex] -> subNodes = malloc(sizeof(struct trieNode*) * 26);
    root -> subNodes[nextIndex] -> letter = *word;
    root -> subNodes[nextIndex] -> subCount = 0;

    if(wordLength == 1) { //checking it is the end of a word
      root -> subNodes[nextIndex] -> occurences = 1;
    } else {
      root -> subNodes[nextIndex] -> occurences = 0;
    }
    //Number of nodes in root increases
    root -> subCount++;
  }

  if(wordLength > 1) { //runs until entire word is entered
    word = word + 1;
    addWordOccurrence(word, wordLength - 1, root -> subNodes[nextIndex]);
  }
  return 0;
}

void printTrieContents(char* word, struct trieNode *root)
{
  if(root -> subCount != 0) {
    //printf("sorting");
    char *temp = malloc(sizeof(char) * (strlen(word)));
    strcpy(temp, word);
    temp[strlen(word)] = '\0';
    strcat(temp, (char*) &(root -> letter));

    //Alphabetic sorting algorithm
    int sort[root -> subCount];
    int start[root -> subCount];

    for(int i = 0; i < root -> subCount; ++i) {
      start[i] = (int) (root -> subNodes[i] -> letter);
    }

    for(int i = 0; i < root -> subCount; ++i) {
      int min = start[i];
      int index = i;
      for(int j = 0; j < root -> subCount; ++j) {
        if(start[j] < min) {
          min = start[j];
          index = j;
        }
      }
      sort[i] = index;
      start[index] = 200;
    }

    for(int i = 0; i < root -> subCount; ++i) {
        printTrieContents(temp, root -> subNodes[sort[i]]);
    }
    free(temp);
  }
  if(root -> occurences > 0) {    
    printf("%s%c: %d\n", (char*) word, (char) root -> letter, root -> occurences);
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
/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
