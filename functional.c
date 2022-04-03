#include "linkedlist.h"
#include <stdio.h>

int addThree(int);
int isEven(int);

////////////////////////

int main(){
  Node *source = seq(0, 10, NULL);
  Node *mapped = map(&addThree ,source);
  Node *filtered = filter(&isEven, mapped);
  printlist(filtered);
  return 0;
}

////////////////////////////////

int addThree(int x) {
  return x + 3;
}

int isEven(int x) {
  return (x % 2) == 0;
}

////////////////////////////////
