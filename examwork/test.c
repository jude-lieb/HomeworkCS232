/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* TODO: structure definitions */
struct trieNode {
  char letter;
  int occurences;
  int subCount;
  struct trieNode** subNodes;
};

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
void indexPage(const char* url);

int addWordOccurrence(const char* word, const int wordLength, struct trieNode *root
		       /* TODO: other parameters you need */);

void printTrieContents(char* word, struct trieNode* root);

int freeTrieMemory(/* TODO: any parameters you need */);

int main(int argc, char** argv){
  //TODO: write the (simple) main function
  //argv[1] will be the URL to index, if argc > 1

  indexPage(argv[1]);

  return 0;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
void indexPage(const char* url)
{
  struct trieNode *root = malloc(sizeof(struct trieNode));
  struct trieNode temp = {'\0',0,0,malloc(sizeof(struct trieNode*) * 26)};
  root = &temp;

  addWordOccurrence("a", 1, root);
  addWordOccurrence("ab", 2, root);
  printTrieContents(&(root -> letter), root);
}

int addWordOccurrence(const char* word, const int wordLength, struct trieNode *root)
{
  //printf("loop ran, char = %c\n", *word);
  int status = -1;
  int nextIndex; //determines which node is the next root

  //checks if current character is in a subnode of the root
  for(int i = 0; i < root -> subCount; ++i) {
    if(*word == root -> subNodes[i] -> letter) {
      status = i;
    }
  }

  if(status != -1) { //if the character already has a node, increment occurrences
    printf("subnode found\n");
    if(wordLength == 1) {
      printf("wordlength = %d incremented letter = %c\n", wordLength, *word);
        root -> subNodes[status] -> occurences++;
    }
    nextIndex = status;
  } else { //if the character is not found, make a new subNode
    nextIndex = root -> subCount;
    root -> subNodes[nextIndex] = malloc(sizeof(struct trieNode*));
    root -> subNodes[nextIndex] -> subNodes = malloc(sizeof(struct trieNode*) * 26);
    root -> subNodes[nextIndex] -> letter = *word;
    root -> subNodes[nextIndex] -> subCount = 0;

    if(wordLength == 1) { //checking it is the end of a word
      printf("occurence added for char %c\n", *word);
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
    char *temp = malloc(sizeof(char) * (strlen(word)));
    strcpy(temp, word);
    temp[strlen(word)] = '\0';
    strcat(temp, (char*) &(root -> letter));
    printf("printing char = %c occ = %d\n", root -> letter, root -> occurences);
    

    for(int i = 0; i < root -> subCount; ++i) {
        printTrieContents(temp, root -> subNodes[i]);
    }
    free(temp);
  }
  if(root -> occurences > 0) {    
    printf("%s%c: %d\n", (char*) word, (char) root -> letter, root -> occurences);
  }
}

int freeTrieMemory(/* TODO: any parameters you need */)
{
  return 0;
}