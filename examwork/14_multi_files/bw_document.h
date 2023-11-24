#ifndef BW_DOCUMENT_H_
#define BW_DOCUMENT_H_

#include "bw_string.h"

struct doc{
  int numLines;

  // an array of numLines lines
  // theLines[i] is a pointer to the ith line
  struct string **theLines;
};

// returns the number of times target occurs in document
int countOccurrences(const struct doc* document, const struct string* target);

// Returns a document that describes the word
//  counts of each word in document
// User should free the returned document
struct doc* getWordCounts(const struct doc* document);

#endif
