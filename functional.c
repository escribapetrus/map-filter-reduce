#include "functional.h"
#include <stdio.h>

int main(){
  Node *source = seq(1, 10, NULL);
  Node *mapped = map(&addThree,source);
  Node *filtered = filter(&isEven, mapped);
  int reduced = reduce(&sum, 0, source);
  printf("source length: %d\n", length(source));
  printf("reduced: %d\n", reduced);
  printf("sum 1..10 == %d\n", (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10));
  printlist(source);
  return 0;
}

int addThree(int x) {
  return x + 3;
}

int isEven(int x) {
  return (x % 2) == 0;
}

int sum(int x, int y){
  return x + y;
}
