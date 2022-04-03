# Map, Filter, Reduce in C: implementing recursive iterators using function pointers
My journey in functional programming had two sides: understanding the paradigm conceptually, and applying it in practice on my daily work. By then, I was working with common tools for the apprentice programmer, far removed from the arcane knowledge of Haskell, and functional Lisp. So, what I had to do was to find means to program in a functional style in the languages I used day-to-day.
    Usually, this starts with three techniques which, though simple for someone whose mind is used to functional programming fundamentals, like recursion and higher-order functions, can prove challenging for someone used to imperative style, for loops and mutable variable assignment. These techniques, which feature in most "functional programming in [blank]" tutorials, are:
    - map(function, list): produces a new list where the elements are the result of the application of the function to the elements of list in the argument;
    - filter(function, list): produces a new list where the elements are those where the application of the elements to the function returns true;
    - reduce: produces the result of the application of the function to all elements over an accumulator.
    
    ```
    list = 1 2 3 4 5 6
    f(x) = x + 2
    
    map(f, list) = 3 4 5 6 7 8
    
    g(x) = x > 3
    
    filter(g, list) = 4 5 6
    
    h(x,y) = x + y
    reduce(h, list) = 21
    ```
 
## Considerations for implementing these in C
There are a few things we must consider when we try to implement these things in C.
    First, we must remember that, in functional programming, data is meant to be immutable, and we dont redefine the values of things. Therefore, we must make sure that our functions do not alter the values of our defined data structures, but rather create new data structures with the values from the source updated by the functions applied to them.
    Second, we must consider that, in C, functions are not first class objects: they cannot be defined inside functions, returned from functions, or passed to functions as arguments. We need to find a way provide our functions with a function to be applied to the values in the data structure.
    
## Implementing a linked list
It is a general rule that recursive algorithms work best with recursively defined data structures: data structures defined by making reference to themselves, such as a linked list or a binary tree. A linked list is a chain of nodes, each of which contains a value and a reference to the next node (and therefore to the rest of the list). In functional programming lingo, this is called a _cons cell_, which defines pairs of elements, where the first element may be the head, and the rest the tail of a list.
    Our tools -- map, filter, reduce -- are recursive algorithms, so it is natural that the lists they iterate over are recursively defined. So, our first step should be to define the data type. 
    We define each element of our linked list as a `struct Node` containing two values: `int data` is the value of the node itself; `Node *next` is a pointer to the next node in the chain. Every node points to a next node, up to the final element in the chain, with points to nothing (null pointer, or zero).
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
  
  It is worth noticing that, when defining this structure, the linked list is defined as a _reference to the first node_, not as the first node itself. To make that explicit, we could have written a type definition `typedef *Node Linkedlist`, where Linkedlist is a pointer to the first node of a linked list.

## Using function pointers to pass functions as arguments
Lambda functions are essential for functional programming, because they provide a clear syntax to create function objects that can be passed to and returned from functions. In Haskell, for example, we can write `\x -> x + 3` to create a function, without having to name it or write it separately from our main program.
    Unfortunately, we don't have that luxury in C. The language does not allow us to write functions inside of other functions, to pass them as arguments, or return them as results of functions. So, we have to find another way to pass functions to our higher-order functions map, filter, and reduce.
    One awesome thing that C does provide is the _function pointer_, a pointer to the memory address of a function. This allows us to pass to a function the address of some function as an argument. For example, we can create a function `apply` that takes a function (rather, a pointer to a function) and a value, and returns the result of applying that function to the value.
    
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

  With this device, we can pass do different operations on a variable, depending on which function we pass an argument.

## Implementing recursive iterators
We have addressed our two considerations, and are now able to define the three high-order functions: map, filter and reduce. Let's explore them um further detail.

### map
Map takes a function and a linked list, and produces a new linked list by applying the function to each element of the argument.
We have to remember that the linked list is a pointer to the head of a list, and the function argument is a pointer to a function. For the type declarations, see the `functional.h` headers in the previous sections. 
        
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



## Problems with our implementation
