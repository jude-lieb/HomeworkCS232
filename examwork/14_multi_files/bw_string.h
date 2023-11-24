#ifndef BW_STRING_H_
#define BW_STRING_H_

#include <stdlib.h>
#include <string.h>

struct string{
  char* theString;
  int length;
  int capacity;
};

// Searches toSearch for the first occurrence of searchingFor.
// Returns the index of the first occurrence, or -1 if there is none.
int findSubstr(struct string *toSearch, struct string *searchingFor);

// Returns a new string, equal to part1:part2
// User should free the return value
struct string* concat(const struct string *part1, const struct string *part2);

#endif
