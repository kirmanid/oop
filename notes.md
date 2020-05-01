# OOP Notes

## Function Signatures

A function's signature includes the function's name and the number, order and type of its formal parameters.
The signature of a function should be unique. Function overloading is when functions have the same name but differect signatures, which is allowed in c++.
Depending on the order and type of the arguments, the appropriate function is auto-called. Usually.

## Pass by value

C++ is a language that passes arguments by _value_, not by _reference_. This means that it copies the contents of arguments into memory by default. However, you can pass stuff by reference if you want.

## Ternary Operator
```c++
(boolean expression)? trueVal : falseVal
```

## First Class Function

Basically a function that you can treat as an argument/object. A useful example is to pass one of these as an "on click" operation to a button.
(You can also just use pointers to funtions)

## Lambda functions

(AKA anonymous funtion)

Lambda functions are functions that you define in-line for convienience. For example, if you want to pass a function as an argument as another function, it might be easier to define it inline.

```c++
[capture](argType argument) -> returnType {/*things happen*/ return 0;}
```

The 'capture' thing states which variables the lambda is allowed to read/write. These are in reference to current scope.
For lambda functions, the return type can inferred by whatever the function ends up returning. If you don't return anything, it's return value is void.

## Pointers, References

```c++
int* px = &x;
// a pointer to an integer, named px, points to the memory adress of x
std::cout << *px << std::endl;
// prints the value that px points to
px = &y; // now px points to the integer y

int& rx{x}; // rx is a _reference_ to the integer x
std::cout << rx << std::endl;
```

You can initialize a pointer as null, meaning it doesn't point to anything, and you can also change what a pointer points to. You can't do that with references.
References can syntactically treated pretty much like the thing that it references, except you have to keep in mind that the values haven't been copied in memory.

## Stack, Heap

* On the stack, memory is de-allocated once you exit a given scope.
* On the heap, you have to manually de-allocate memory once you use it.
* the 'new' keyword before a variable allocates memory on the heap, as opposed to the stack
    * the 'delete' keyword before the same variable de-allocates the memory on the heap

```c++
Thing* thPtr = new Thing{}; // creates a Thing object on the heap, and now thPtr points to it
```

This works fine, but can sometimes be a pain. So people made unique pointers.

## Unique Pointers

Unique pointers express ownership, meaning that there can only be one 'owner' of something.

(make_unique, move) 

## TODO:
* enum classes, new style, not old-style
* finish unique pointer entry
* arrow operator (basically just dot operator but for pointers)
* virtuals
* base classes, derived classes, inheritance
