#include "functional.h"
#include <stdlib.h>
#include <stdio.h>

Node *cons(int el, Node *n){
   Node *node = (Node *) (malloc(sizeof(Node)));
   node->data = el;
   node->next = n;

   return node;
 }

Node *seq(int fst, int lst, Node *acc){
  if (fst <= lst) {
    acc = cons(lst, acc);
    return seq(fst, lst - 1, acc);
  }
  else {
    return acc;
  }
}

int length(Node *n){
  if (n == 0) return 0;
  return 1 + length(n->next);
}

void printlist(Node *n){
  if (n != 0) {
    printf("%d ", n->data);
    printlist(n->next);
  }
  else printf("\n");
}
