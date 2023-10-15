#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listNode{
  char addr[100];
  struct listNode *next;
};

void insert(struct listNode *pNode, const char *addr);

int main() {
    struct listNode list1 = {"https://users.pfw.edu/chenz/testWeb/page_000003.html", NULL};

    const char temp[] = "https://users.pfw.edu/chenz/testWeb/page_000003.html";
    insert(&list1, temp);
    return 0;
}


void insert(struct listNode *pNode, const char *addr) {
    if(strcmp(pNode -> addr, addr) == 0) {
       printf("this worked!");

    } else {
      printf("not a match");
    }
}