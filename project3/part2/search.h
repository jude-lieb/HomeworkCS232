#ifndef SEARCH_H_
#define SEARCH_H_

int *search(long double *idfScores, long double *urlScores, char** words, int wordCount, struct listNode *addr, struct trieNode **trieList, int trieCount, int termCount[], int *urlCount);
int getOccurrences(struct trieNode *trie, char *word);



#endif