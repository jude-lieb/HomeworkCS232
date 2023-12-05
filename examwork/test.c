
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv){
  int num = 20;
  char *str = " 1";
  int res = sscanf(str, "%d", &num);
  if(res) {
    printf("%d",num);
  }

  return 0;
}