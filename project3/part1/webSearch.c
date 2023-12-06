#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crawler.h"
#include "indexPage.h"

int main(int argc, char **argv) {
    if(argc < 4) {
        printf("%s\n", "Not enough arguments.");
        return 0;
    }

    int seed = atol(argv[3]);
    srand(seed);
    char *line = malloc(sizeof(char) * (MAX_ADDR_LENGTH + 5));
    char *url = malloc(sizeof(char) * MAX_ADDR_LENGTH);
    char *newUrl = malloc(sizeof(char) * MAX_ADDR_LENGTH);
    FILE *urlFile = fopen(argv[1], "r");
    int hopNum = 0;
   
    int n = 0;
    int res, hopLimit;
    int MAX_QUERY_LEN = 100;
    int MAX_N = atoi(argv[2]);
    int *termCount = malloc(sizeof(int) * MAX_N);

    struct trieNode **trieList = malloc(sizeof(struct trieNode*) * MAX_N);
    struct listNode *pListStart = malloc(sizeof(struct listNode));
    pListStart -> next = NULL;
    pListStart -> addr[0] = '\0';

    printf("Indexing...\n");

    while(fgets(line, 100, urlFile) != NULL && n < MAX_N) {
        if(sscanf(line,"%s%d", url, &hopLimit) < 2) {
            return 0;
        }

        hopNum = 0;
        while(1) {
            if(!contains(pListStart, url)) {
                printf("%s\n", url);
                trieList[n] = indexPage(url, &termCount[n]);
                insertBack(pListStart, url);
                n++;
            }
            hopNum++;
            if(hopNum <= hopLimit && n < MAX_N) {
                res = getLink(url, newUrl, MAX_ADDR_LENGTH);
                if(!res) {
                    break;
                }
                
                strncpy(url, newUrl, MAX_ADDR_LENGTH);
                
            } else {
                break;
            }
        }
    }

    //Cleanup
    fclose(urlFile);
    free(line);
    free(url);
    free(newUrl);
    destroyList(pListStart);
    free(termCount);
   
    for(int i = 0; i < n; ++i) {
        freeTrieMemory(trieList[i]);
    }
    free(trieList);
    
    return 0;
}