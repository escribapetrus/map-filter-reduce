typedef struct Node {
  int data;
  struct Node* next;
} Node;

Node *cons(int, Node *);

Node *seq(int, int, Node *);

void printlist(Node *);

//////////

typedef int (*fp) (int);
typedef int (*gp) (int, int);

Node *map(fp, Node *);
Node *filter(fp, Node *);
Node *reduce(gp, Node *, Node *);
