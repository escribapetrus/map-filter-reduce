#include "linkedlist.h"
#include <stdio.h>

Node *map(fp fp, Node *n){
  if (n == NULL) return NULL;

  int val = (*fp)(n->data);
  return cons(val, map(fp, n->next));
}
