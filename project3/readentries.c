#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "readentries.h"
#include "indexPage.h"
#include "crawler.h"
#include "search.h"

void readInputs(struct trieNode **trieList, struct listNode *pListStart, int *termCount, int numPages) {
    //Reading entries
    int MAX_QUERY_LEN = 100;
    int queriesRead;
    char **searchTerms = malloc(sizeof(char*) * 20);
    char *query = malloc(sizeof(char) * MAX_QUERY_LEN);
    char entry[MAX_QUERY_LEN];

    long double *idfScores = malloc(sizeof(long double) * 20);
    long double *urlScores = malloc(sizeof(long double) * 3);
    struct listNode *currentList;
    char check;
    int error;
    
    do { 
        printf("\nEnter a web query: ");
        queriesRead = 0;
        error = 0;
        int isValid, i, size;
        isValid = 0;

        if(fgets(entry, 100, stdin) == NULL) {
            break;
        }

        char *current = entry;
        size = strnlen(entry, 100);
        char entryCopy[100];
        strncpy(entryCopy, entry,100);
        
        for (i = 0; i < size; ++i) {
            if (entry[i] >= 'a' && entry[i] <= 'z') {
                isValid = 1;
            } else if(entry[i] != ' ' && entry[i] != '\n') {
                fprintf(stderr,"Please enter a query containing only lower-case letters.\n");
                error = 1;
                break;
            } else {
                check = entry[i];
                
                if (isValid) {
                    // null char ends each word at each non-alphabetic char
                    entry[i] = '\0';
                    
                    searchTerms[queriesRead] = malloc(sizeof(char) * MAX_QUERY_LEN);
                    strncpy(searchTerms[queriesRead], current, MAX_QUERY_LEN);
                    queriesRead++;
                    isValid = 0;
                    
                }
                
                //ending at newline char
                if(check == '\n') {
                    entryCopy[i] = '\0';    
                    i = 200;
                } 
                current = entry + i + 1;
            }
        }

        //moves to next input if any errors occur.
        if(error == 1) {
            for(int i = 0; i < queriesRead; ++i) {
                free(searchTerms[i]);
            }
            continue;
        }

        if(queriesRead > 0) {
            printf("Query is \"%s\".\n", entryCopy);
            printf("IDF scores are\n");
            int numUrls = 0;
            
            int *results = search(idfScores, urlScores, searchTerms, queriesRead, pListStart, trieList, numPages, termCount, &numUrls);
            
            for(int i = 0; i < queriesRead; ++i) {
                printf("IDF(%s): %.7Lf\n", searchTerms[i], idfScores[i]);
            }
            
            printf("Web pages:\n");
            for(int i = 0; i < numUrls; ++i) {
                currentList = pListStart;
                for(int j = 0; j < results[i]+1; ++j) {
                    currentList = currentList -> next;
                }
                printf("%d. %s (score: %.4Lf)\n", i + 1, currentList -> addr, urlScores[i]);
            }
            free(results);

            for(int i = 0; i < queriesRead; ++i) {
                free(searchTerms[i]);
            }
        }
    } while(entry[0] != '\n');
    
    free(searchTerms);
    free(query);
    free(idfScores);
    free(urlScores);
}
