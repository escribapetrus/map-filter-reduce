#include "functional.h"
#include <stdio.h>

int main(){
  // define a source sequence to operate on: [1, 2, ..., 10]
  Node *source = seq(1, 10, NULL);

  printlist(source);
  // map the function addThree to the source sequence
  // the content of the source is preserved (immutability)
  printlist(map(&addThree, source));

  // filter the source sequency using the predicate function isEven
  // predicate functions are functions that return a boolean value
  printlist(filter(&isEven, source));

  // reduce the source sequence by applying the sum function to every element and an accumulator
  // the reduce function is also known as foldr
  printf("%d\n", reduce(&sum, 0, source));

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
