# Chapter 4 - Review

### What is a computation?
Producing ouput from input.

### What is mean by inputs and outputs to a computation? List some examples.
Example inputs: Keyboard, mouse, read from file, other programs or parts of them.

Example output: Show on screen, save to file, pass data to other programs or parts of them.

### List the three requirements a programmer should keep in mind when expressing computations.
Correctness, simplicity and efficiency.

### What does an expression do?
It takes a collection of operands and operators, interprets them and computes a value.

### What's the difference between a statement and an expression?
Statements are the instructional units of the program: Run in sequence, sometimes describing an expression, in other cases loops, conditionals, jumps in control flow, etc.

### What is an lvalue? List the operators that require an lvalue and explain why.
An lvalue is the operand used on the left-hand side of an assignment or initialization.
```c++
// Operators that deal with assignment:
int lvalue_var = 0;
// or compound assignment:
lvalue_var += 1;
//require an lvalue for this reason.
```

### What is a constant expression
An expression composed exclusively of constants.

### What is a literal?
A fixed value hard-coded into the source file that can be stored in a variable or used in calculations.

### What is a symbolic constant and why do we use them?
A named object whose value cannot be altered after initilization. Adds invariable values to our code and gives them meaningful names we can refer to.

### What's a magic constant? Give examples.
Non-obvious literals not defined as symblic constants.
```c++
double circle_area_a = 3.1415926535 * 2.5 * 2.5; // magic constant pi,
						   					     // magic value radius

// refactored
constexpr double pi { 3.1415926535 };
double radius { 2.5 };
double circle_area_b = pi * radius * radius;
```