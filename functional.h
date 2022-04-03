/*
   Type definitions, where we define:
   - Linked list
   - Function pointers
*/
typedef struct Node {
  int data;
  struct Node* next;
} Node;
typedef int (*fp) (int);
typedef int (*gp) (int, int);

/*
  Function declarations for constructing,
  analysing, and printing linked lists.
*/
Node *cons(int, Node *);
Node *seq(int, int, Node *);
int length(Node *);
void printlist(Node *);
/*
   Recursive iterators
*/
Node *map(fp, Node *);
Node *filter(fp, Node *);
int reduce(gp, int, Node *);
/*
 Functions passed as arguments to iterators.
*/
int isEven(int);
int sum(int, int);
int addThree(int);
