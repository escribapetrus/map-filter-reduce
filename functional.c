#include "functional.h"
#include <stdio.h>

int main(){
  Node *source = seq(1, 5, NULL);
  int reduced = reduce(&sumTen, 0, source);
  printf("source length: %d\n", length(source));
  printf("reduced: %d\n", reduced);
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

int sumTen(int x, int y){
  return (x * 10) + y;
}
