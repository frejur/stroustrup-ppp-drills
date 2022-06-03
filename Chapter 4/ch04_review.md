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
Generally speaking, the lvalue is the operand used on the left-hand side of an assignment or initialization. It refers to the location in memory of an object or function.
```c++
// Operators that deal with assignments:
int lvalue_var = 0;
// or compound assignments:
lvalue_var += 1;
// require an lvalue for this reason.

// Increment / Decrement operators are also forms of assignment
++lvalue_var; // lvalue += 1
lvalue_var = --lvalue_var; // lvalue = lvalue -= 1
```

### What is a constant expression
An expression composed exclusively of constants and/or literals.

### What is a literal?
A fixed value hard-coded into the source file that can be stored in a variable or used in calculations.

### What is a symbolic constant and why do we use them?
A named object whose value cannot be altered after initilization. Adds useful values to our code and gives them meaningful names for easier access and clearer syntax.

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

### Name some operators typically used for integers and floating-point values.
Arithmetic operators: + - / *
Logical operators: == != > <

### What operators can be used on integers but not floating point numbers?
Modulo %

### What are some operators that can be used for strings?
```c++
string s { "t" }; // the + operator
s += "es" + s;    // "test"
s != "test";      // logical: false

cout << s << endl;
```

### When would a programmer prefer a switch statement over an if statement?
When you want to test the equality of a variable or expression against a list of many values.

### What are some common problems with switch-statements?
Limited use: the conditions must be constant expressions.
Gotcha: Forgetting to add 'break' after each case block.

### Anatomy and order of operations of a for loop header.
for (A;B;C)
A. Expression run once at the beginning, usually intializing an iterator variable.
B. Expression run at the start of each iteration, if it evaluates to false the loop is ended.
C. Expression run at the end of each iteration, usually incrementing a an iterator variable.

### When should a for loop be used instead of a while loop and vice-versa?
For loops provide a concise way to initialize, check and increment on one header line. This workflow also goes a long way to avoid infinite loops. However, while loops are necessary when you can't determine a finite number of iterations beforehand.

### How do you print the numeric value of a char?
```c++
cout << 'A' << (int)'A' << endl; // type conversion
```

### Meaning of the function definition char foo(int x)
A function by the name of __foo__ takes one __integer__ value as an argument and returns a value of the type __char__.

