The functional programming journey has a dual aspect: understanding the paradigm conceptually, and applying it in practice on the daily work. When working with the current common tools for programmer, however, we are usually far removed from the arcane knowledge of Haskell and functional Lisp. Sometimes, what we have to do is to find ways to program in a functional style in the languages we use day to day, like Python or Javascript.

Usually, this starts with three techniques which, though simple for someone whose mind is used to functional programming fundamentals, like recursion and higher-order functions, can prove challenging for someone used to the imperative style, for loops and mutable variable assignment. These techniques, which feature in most "functional programming in [blank]" tutorials, are:

- map(function, list): produces a new list where the elements are the result of the application of the function to the elements of list in the argument;
- filter(function, list): produces a new list where the elements are those where the application of the elements to the function returns true;
- reduce: produces the result of the application of the function to all elements over an accumulator.

They are higher-order functions: functions that receive other functions as arguments.

```
list = 1 2 3 4 5 6

f(x) = x + 2
map(f, list) = 3 4 5 6 7 8
    
g(x) = x > 3
filter(g, list) = 4 5 6
    
h(x,y) = x + y
reduce(h, list) = 21
```

In this article, we are attempting to implement this functionality in the C programming language. Please note that this is just an exercise, not a recommendation for a serious style of programming in this language.
 
## Considerations for implementing functional tools in C
There are a few things we must consider before we try to implement these functional tools in C.

First, we must remember that, in functional programming, data is meant to be immutable. Therefore, we must make sure that our functions do not alter the values of our variables and data structures, but rather create new variables and data structures, whose values are derived com computations applied to a source.

Second, we must consider that, in C, functions are not first class objects: they cannot be defined inside functions, returned from functions, or passed to functions as arguments. We need to find a way provide our functions with a function to be applied to the values in a data structure.
    
## Implementing a linked list
It is a general rule that recursive algorithms work best with recursively defined data structures: data structures defined by making reference to themselves, such as a linked list or a binary tree. 

A linked list is a chain of nodes, each of which contains a value and a reference to the next node (and therefore to the rest of the list). 

In functional programming lingo borrowed from Lisp, we can define a linked list in terms of a _cons cell_, a pair of elements (a, b), where the _head_ is the first element, and the _tail_ is a recursive sequence of cons cells ending on an empty cell.

Our tools -- map, filter, reduce -- are recursive high-order-functions, so it is natural that the lists they iterate over are recursively defined. Our first step should be to define the data type. 

We define each element of our linked list as a `struct Node` containing two values: `int data`, the value of the node itself; `Node *next`, a pointer to the next node in the chain. Every node points to a next node, up to the final element in the chain, with points to nothing (nil pointer, or zero).

Also, we define a `cons` function, which allows us to create a linked list. It receives an integer value and a list to add it to, allocates space in memory for a node, assigns the value as its data, and plugs the node into a list by pointing `next` to the `head` of the list. 
            
```c
/* functional.h */
typedef struct Node {
  int data;
  struct Node* next;
} Node;

Node *cons(int, Node *);
  
/* linkedlist.c */
#include "functional.h"
#include <stdlib.h>

Node *cons(int el, Node *n){
  Node *node = (Node *) (malloc(sizeof(Node)));
  node->data = el;
  node->next = n;

  return node;
 }
```
  
It is worth mentioning that the linked list is defined as a pointer to the first node_, not as the first node itself. To make that explicit, we could have written a type definition `typedef *Node Linkedlist`, where Linkedlist is a pointer to the first node of a linked list.

## Using function pointers to pass functions as arguments
Lambda functions are essential for functional programming, because they provide a clear syntax to create function objects that can be passed to and returned from functions. In Haskell, for example, we can write `\x -> x + 3` to create a function, without having to name it or write it separately from our main program.

Unfortunately, we don't have that luxury in C. The language does not allow us to write functions inside of other functions, to pass them as arguments, or return them as results of functions. So, we have to find another way to pass functions to our higher-order functions map, filter, and reduce.

One awesome thing that C does provide is the _function pointer_, a pointer to the memory address of a function. This allows us to pass the address of a function as an argument. For example, we can create a function `apply` that takes a function (or rather, a pointer to a function) and a value, and returns the result of applying that function to the value.
    
```c
/* functional.h */
typedef int (*fp) (int);
typedef int (*gp) (int, int);

int apply(fp, int);
    
/* apply.c */
#include "functional.h"
int apply(fp fp, int x){
  return (*fp)(x)
}
```

With this device, we can do different operations on a variable, depending on which function we pass an argument to `apply`.

## Implementing recursive iterators
We have addressed our two considerations, and are now able to define the three high-order functions: map, filter and reduce. They are very simple to implement, if we remember to compute recursively-defined data structures with recursion. 

Our three functions take the first element of the list (the `head`), apply a function to it, and proceed to compute the next elements (the `tail`) according to the result, recursively, until it reaches a nil pointer, at which point the list is exhausted and the computation stops.

Let us implement and explore them in further detail.

### map
Map takes a function and a linked list, and produces a new linked list by applying the function to each element of the list.
        
```c
/* functional.h */
Node *map(fp, Node *);

/* iterators.c */
Node *map(fp fp, Node *n){
  if (n == 0) return 0;
  int val = (*fp)(n->data);
  return cons(val, map(fp, n->next));
} 
```

We take the value of the head of the list, apply the function specified in the arguments, pointed to by `fp`, and `cons` the result into a new list build by the recursive application of `map` to the next elements. 

Let us define a few different functions that can be passed to `map`, and create a transformed linked list.

```c
/* functional.h */
int addThree(int);
int doDouble(int);
int toFour(int);

/* main.c */
int main(){
  Node *src = seq(1, 5, NULL);
  Node *li = map(&addThree, source);
  Node *lj = map(&doDouble, source);
  Node *lk = map(&toFour, source);
        
printlist(li); // prints 4 5 6 7 8
printlist(lj); // prints 2 4 6 8 10
printlist(lk); // prints 4 4 4 4 4
  
  return 0;
}

int addThree(int x) {
  return x + 3;
}
int doDouble(int x){ 
  return x * 2;
}
int toFour(int x){
  return 4;
}
```

### filter
Filter takes a function and a linked list, and produces a new linked list by applying the function to each element of the argument, conserving or discarding it, depending on whether the function returns true or false.
        
```c
/* functional.h */
Node *filter(fp, Node *);

/* iterators.c */
Node *filter(fp fp, Node *n){
  if (n == 0) return 0;
  if ((*fp)(n->data))
    return cons(n->data, filter(fp, n->next));
  else
    return filter(fp, n->next);
}
```

We pass to the `filter` what is called a _predicate_: a function that returns a boolean value. We take the value of the head of the list, and apply the predicate to it. If it returns true, we `cons` that value into a new list built by the recursive application of `filter` to the next elements. If it returns false, we discard it, and proceed with the recursion of the tail.

Let us define a few different functions that can be passed to `filter`, and create a filtered list.
    
```c
/* functional.h */
int isEven(int);
int greaterThanTwo(int);

/* main.c */
int main(){
  Node *src = seq(1, 5, NULL);
  Node *li = filter(&isEven, source);
  Node *lj = filter(&greaterThanTwo, source);
        
  printlist(li); // prints 2 4
  printlist(lj); // prints 3 4 5
  
  return 0;
}

int isEven(int x) {
  return (x % 2 == 0);
}
int greaterThanTwo(int x){ 
  return x > 2;
}
```
    
### reduce
Reduce takes a function, a linked list, and an accumulator, and returns the result of applying the function to the accumulator and to every element of the list.

```c
/* functional.h */
Node *filter(fp, Node *);

/* iterators.c */
int reduce(gp gp, int acc, Node *n){
  if (n == 0) return acc;
  int val = (*gp)(n->data, acc);
  return reduce(gp, val, n->next);
}
```
    
The `reduce` function receives a _binary operator_: a function with two arguments, just like the basic arithmetic operators. We take the head of the list and apply the binary operator to it, together with the accumulator. Then, we set the result as the new value of the accumulator, and recursively repeat the operation on the next elements of the list.

Let us define a few different functions that can be passed to `reduce`, and compute the value of a reduced list.

```c
/* functional.h */
int sum(int, int);
int sumTimesTen(int, int);

/* main.c */
int main(){
  Node *src = seq(1, 5, NULL);
  int i = reduce(&sum, source);
  int j = filter(&greaterThanTwo, source);
        
printf("%d\n", i); // prints 15
printf("%d\n", j); // prints 150
  
  return 0;
}

int sum(int x) {
  sum;
}
int sumTimesTen(int x, int y){ 
  return (x * 10) + y;
}
```

## Conclusion
We have developed a way to implement the popular tools for a functional programmer -- map, filter, reduce -- in C, a language that does not really support lambda functions. 

To recap, the first thing we had to consider was the data structure on which we wanted to operate. We chose the linked list, the standard data structure for collecting items in functional programming languages like Scheme, Haskell and Erlang. We defined or linked list as pointers to nodes, every node being a structure that stores some data (an integer) and points to the next item of the list. The end of the list is marked by a nil pointer (a zero value). We have also define a `cons` function that allows us to construct a list by plugging elements to an existing list (or to an empty list, represented by a nil pointer).

One thing to keep in mind is that this is meant to be merely a study on recursive data structures and function pointers, and not a proposal for _functional programming in C_. One major problem with our approach is that, in order to achieve the immutability of data structures, we are allocating new data to memory, but we haven't provided any way to clean the unnecessary or unused data. That would require a garbage collector, something that is not provided in C, and is beyond the scope of this exercise.

Another thing worth mentioning is that our functions are limited to working with integer types `int`. It would have been nice to implement some sort of _parametric polymorphism_, that is, defining of function types to accept any types of arguments.

I would appreciate any comments, corrections, critiques or suggestions.

-------------

Functions used but not explained in the article:

```c
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

```
