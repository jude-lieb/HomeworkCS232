#ifndef INDEXPAGE_H_
#define INDEXPAGE_H_

#define MAX_LEN 10000

struct trieNode
{
  char letter;
  int occurences;
  int subCount;
  struct trieNode **subNodes;
};


struct trieNode *createNode(char letter);

struct trieNode *indexPage(const char *url, int *numTerms);

int addWordOccurrence(const char *word, const int wordLength, struct trieNode *root);

void freeTrieMemory(struct trieNode *node);

int getText(const char *srcAddr, char *buffer, const int bufSize);

#endif