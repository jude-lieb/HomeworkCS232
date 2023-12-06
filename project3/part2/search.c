#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indexPage.h"
#include "crawler.h"
#include "search.h"
#include "math.h"

int *search(long double *idfScores, long double *urlScores, char** words, int wordCount, struct listNode *addr, struct trieNode** trieList, int trieCount, int termCount[], int *urlCount) {
    long double totalScore = 0;
    int occ[trieCount];
    long double tfScore;
    long double idfScore; 
    long double pageScores[trieCount];
    int docsWithTerm[wordCount];
    long double wordScore;
    long double occurrences;
    long double terms;
    long double logTop;
    long double logBottom;

    //finding scores for each word
    for(int i = 0; i < wordCount; ++i) {
            docsWithTerm[i] = 0;
            wordScore = 0;
            for(int j = 0; j < trieCount; ++j) {
                occ[j] = getOccurrences(trieList[j], words[i]);
                if(occ[j] > 0) {
                    docsWithTerm[i]++;
                }
            }
            //Calculating IDF Score
            logTop = (long double) (1.0 + (long double) trieCount);
            logBottom = (long double) (1.0 + (long double) docsWithTerm[i]);
            idfScore = log(logTop / logBottom);
            idfScores[i] = idfScore;
    }

    //calculating overall scores for each page
    for(int l = 0; l < trieCount; ++l) {
        pageScores[l] = 0;
        for(int i = 0; i < wordCount; ++i) {
            //Calculating TF score
            occurrences = (long double) getOccurrences(trieList[l], words[i]);
            terms = (long double) termCount[l];
            tfScore = occurrences / (long double) terms;
            totalScore = tfScore * idfScores[i]; 
            pageScores[l] = pageScores[l] + totalScore;
        }
    }

    long double max;
    int maxIndex;
    int *results = malloc(sizeof(int) * 3);

    //Finding top 3 scoring pages
    for(int j = 0; j < 3; ++j) {
        max = 0;
        maxIndex = -1;
        for(int i = 0; i < trieCount; ++i) {
            if(pageScores[i] > max) {
                maxIndex = i;
                max = pageScores[i];
                urlScores[j] = max;
            }
        }
        results[j] = maxIndex;
        if(maxIndex != -1) {
            *urlCount = *urlCount + 1;
        }
        pageScores[maxIndex] = -1;
    }
    return results;
}

int getOccurrences(struct trieNode *trie, char *word) {
    int status = -1;
    for(int i = 0; i < trie -> subCount; ++i) {
        if(*word == trie -> subNodes[i] -> letter) {
            status = i;
            break;
        }
    }   
    if(status == -1) { //letter not found
        return 0;
    } else { //letter is found in subnode array
        if(strnlen(word, 20) == 1) {
            return trie -> subNodes[status] -> occurences;
        } else {
            word = word + 1;
            return getOccurrences(trie -> subNodes[status], word);
        }
    }
}