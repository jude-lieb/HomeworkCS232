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
};

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
void indexPage(const char* url);

int addWordOccurrence(const char* word, const int wordLength
		       /* TODO: other parameters you need */);

void printTrieContents(/* TODO: any parameters you need */);

int freeTrieMemory(/* TODO: any parameters you need */);

int getText(const char* srcAddr, char* buffer, const int bufSize);

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
  const int amount = 300000;
  //allocating space for text buffer
  char *buffer = malloc(sizeof(char) * amount);
  //using url argument to get text and put it in buffer
  int numChars = getText(url, buffer, amount);
  printf("%d", numChars);

  char *current = '\0';

  for(int i = 0; i < numChars; ++i) {
    if((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z')) {
      tolower(buffer[i]);
      strcat(current, (char) buffer[i]);
    } else {
      addWordOccurrence(current, strlen(current));
      *current = '\0';
    }
  }

  

}

int addWordOccurrence(const char* word, const int wordLength
		       /* TODO: other parameters you need */)
{
  return 0;
}

void printTrieContents(/* TODO: any parameters you need */)
{

}

int freeTrieMemory(/* TODO: any parameters you need */)
{
  return 0;
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