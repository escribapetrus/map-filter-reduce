typedef int (*fp) (void *);
typedef int (*gp) (void *, void *);

Node *map(fp, Node *);
Node *filter(fp, int *);
Node *reduce(gp, int, int *);
