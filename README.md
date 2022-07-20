# Map, Filter, Reduce in C: recursive high-order functions using pointers

This repository contains a set of functions that serve as a study for a possible implementation of the _map_, _filter_ and _reduce_ higher-order functions in C, and how to reference functions using pointers. This is meant to be merely a study on recursive data structures and function pointers, and not a proposal for _functional programming in C_.

If you're interested, you can [read the article](https://dev.to/escribapetrus/map-filter-reduce-in-c-recursive-high-order-functions-using-pointers-376n) on the web (or in the file `article.md`).  

Contents:
- `iterators.c`: implements a higher-order function that receives a function pointer and a list (linked list), and recursively applies the function to every element
- `linkedlist.c`: implements a linked list, a recursive data type used for collecting data in functional programming languages
- `functional.c`: implements some functions that can be passed as arguments (through pointers) to our higher-order functions

## Lambda functions
Lambda functions are essential for functional programming, because they provide a clear syntax to create function objects that can be passed to and returned from functions.

Functions are not first-class objects in C: they cannot be returned from functions or passed to functions as arguments. However, the language does provide function pointers,  pointers to the memory addresses of functions. For example, we can create a function `apply` that takes a function pointer and a value, and returns the result of applying the function to the value.

```c
typedef int (*fp) (int);

int apply(fp fp, int x){
  return (*fp)(x)
}
```

## For further development
One major problem with our approach is that, in order to achieve the immutability of data structures, we are allocating new data to memory, but we haven't provided any way to clean the unnecessary or unused data. That would require a garbage collector, something that is not provided in C, and is beyond the scope of this exercise.

Another thing worth mentioning is that our functions are limited to working with integer types `int`. It would be nice to implement some sort of _parametric polymorphism_, that is, defining of function types to accept any types of arguments.

I would appreciate any comments, corrections, critiques or suggestions.


