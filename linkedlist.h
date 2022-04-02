typedef struct Node {
  int data;
  struct Node* next;
} Node;

Node *cons(int, Node *);

Node *seq(int, int, Node *);
