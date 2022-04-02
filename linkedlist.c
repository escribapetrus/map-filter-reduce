#include "linkedlist.h"
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

void printlist(Node *n){
  if (n != NULL) {
    printf("%d ", n->data);
    printlist(n->next);
  }
  else printf("\n");
}

int main(){
  Node *last = NULL;
  Node *lis = seq(4, 8, last);

  printlist(lis);

  return 0;
}
