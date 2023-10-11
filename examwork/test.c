#include <stdio.h>
#include <stdlib.h>

struct listNode{
  char addr[100];
  struct listNode *next;
};

void insert(struct listNode *pNode, const char *addr);

int main() {
    struct listNode list1 = {"sup", NULL};

    const char temp[] = "sup1";
    insert(&list1, temp);

    printf("%s", list1.addr);
    return 0;
}


void insert(struct listNode *pNode, const char *addr) {
    struct listNode list2 = {addr, NULL};
    pNode -> next = &list2;

}