#include "linkedlist.h"
#include <stdio.h>

int addThree(int);
int addTen(int);

////////////////////////

int main(){
  Node *source = seq(0, 10, NULL);

  Node *mapped = map(&addThree ,source);

  printlist(mapped);
  return 0;
}

////////////////////////////////

int addThree(int x) {
  return x + 3;
}


int addTen(int x){
  return x + 1;
}

////////////////////////////////
