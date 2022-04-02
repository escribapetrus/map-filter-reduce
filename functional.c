//#include "functional.h"
#include <stdio.h>

int addThree(int);
int addTen(int);

typedef int (*fp) (void *);
typedef int (*gp) (void *, void *);

int *map(fp, int *, int *);
int *filter(fp, int *);
int reduce(gp, int, int *);

////////////////////////

int main(){



  return 0;
}

////////////////////////////////

int addThree(int x) {
  return x + 3;
}


int addTen(int x){
  return x + 1;
}

////////////////////////////////

//arr map(func, arr)
int *map(fp fp, int *arr, int *head){
    *arr = (*fp)(arr);

    if (arr == NULL) {
      return head;
    }
    else {
      return map(fp, arr++, head);
    }
}

// arr filter(func, arr)


// arr reduce(func, acc, arr)
