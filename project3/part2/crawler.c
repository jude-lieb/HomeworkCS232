#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crawler.h"

int contains(const struct listNode *pNode, const char *addr){
  if(pNode != NULL && addr != NULL) {
      if(!strncmp(pNode -> addr, addr, MAX_ADDR_LENGTH)) {
        return 1;
      } else {
        return contains(pNode -> next, addr);
      } 
  }
  return 0;
}

void insertBack(struct listNode *pNode, const char *addr){
  if(pNode -> next == NULL) {
    //allocating memory for new node
    struct listNode *temp = malloc(sizeof(struct listNode));
    //filling contents of node structure
    strncpy(temp -> addr, addr, MAX_ADDR_LENGTH);
    temp -> next = NULL;
    pNode -> next = temp;
  } else {
    insertBack(pNode -> next, addr);
  }
}

void destroyList(struct listNode *pNode){
  if(pNode -> next == NULL) {
    free(pNode);
  } else {
    //creating temporary node to allow for next function call
    struct listNode temp = *pNode;
    free(pNode);
    destroyList(temp.next);
  }
}
  
int getLink(const char* srcAddr, char* link, const int maxLinkLength){
  const int bufSize = 1000;
  char buffer[bufSize];

  int numLinks = 0;

  FILE *pipe;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getLinks.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n", buffer);
    return 0;
  }

  fscanf(pipe, "%d\n", &numLinks);

  if(numLinks > 0){
    int linkNum;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    for(linkNum=0; linkNum<numLinks; linkNum++){
      fgets(buffer, bufSize, pipe);
      
      if(r < (linkNum + 1.0) / numLinks){
		    break;
      }
    }

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';
    
    /* get rid of the newline */
    {
      char* pNewline = strchr(link, '\n');
      if(pNewline != NULL){
		    *pNewline = '\0';
      }
    }
  }

  pclose(pipe);

  if(numLinks > 0){
    return 1;
  }
  else{
    return 0;
  }
}