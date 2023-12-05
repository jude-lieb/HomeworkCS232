#ifndef CRAWLER_H_
#define CRAWLER_H_

#define MAX_ADDR_LENGTH 1000

struct listNode{
  char addr[MAX_ADDR_LENGTH];
  struct listNode *next;
};

int contains(const struct listNode *pNode, const char *addr);

void insertBack(struct listNode *pNode, const char *addr);

void printAddresses(const struct listNode *pNode);

void destroyList(struct listNode *pNode);

/*
 * getLink returns 1 if a link was found and 0 otherwise.
 * If a link was found, "link" will be filled in with the web address.
 */
int getLink(const char* srcAddr, char* link, const int maxLinkLength);

#endif