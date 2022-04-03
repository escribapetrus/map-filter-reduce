#include "linkedlist.h"

Node *map(fp fp, Node *n){
  if (n == 0) return 0;

  int val = (*fp)(n->data);
  return cons(val, map(fp, n->next));
}

Node *filter(fp fp, Node *n){
  if (n == 0) return 0;

  if ((*fp)(n->data))
    return cons(n->data, filter(fp, n->next));
  else
    return filter(fp, n->next);
}

int reduce(gp gp, int acc, Node *n){
  if (n == 0) return acc;

  int val = (*gp)(n->data, acc);
  return reduce(gp, val, n->next);
}
