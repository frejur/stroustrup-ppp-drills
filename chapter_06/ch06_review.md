# Chapter 06 - Review Questions

### What do we mean by "Programming is understanding"?
Before instructing someone else (the computer) how to solve a problem you first have to try to understand the problem and its solution. The closer the program gets to being finished the more you understand.

### The chapter details the creation of a calculator program. Write a short analysis of what the calculator should be able to do.
Convert keyboard input into mathematical expressions, parse, calculate and output the result.

### How do you break a problem up into smaller manageable parts?
Look for parts of the solution that can be brought in from external libraries.
Look for parts that can be separately described.

### Why is creating a small, limited version of a program a good idea?
You've never fully understood the problem when starting off. A prototype will expose problems in your understanding, ideas and tools, sometimes it becomes clear that the implementation needs to be redesigned completely.

### Why is feature creep a bad idea?
More than often it's like openining a can of worms and leads to production delays. New features take time to implement and troubleshoot, they increase complexity and may break other parts of the program.

### What are the three main phases of software development?
Analysis, Design and Implementation.

### What is a use case?
A sketch of how a user might interact with the program and how the program should respond. 

### What is the purpose of testing?
To attempt to weed out any bugs and errors before an actual user has the misfortune to run into them.

### Describe the difference between a Term, an Expression, a Number, and a Primary.
A valid Expression will ultimately consist of Numbers combined using arithmetic operators and parentheses:
- An Expression is a either a single Term or Terms combined using addition or subtraction.
- A Term is either a single Primary or Primaries combined using multiplied by, divided by or divided by and returning the remainder (modulo %).
- A Primary is a single Number or an Expression surrounded by parentheses.
- A Number is always a floating-point-literal

### Take the expression (17+4)/(5–1) and break it down into Terms, Expressions, Primarys, and Numbers
Both expressions contained within the parentheses are parsed as Primaries, Terms and Expressions. When joined by the '/' operator they are parsed as a Term according to the Term / Primary rule, which is consequently an Expression.
```
(17+4)  is:     ("("Expression")")  ->          a Primary   a Term      an Expression
17      is:     a float-literal     a Number    a Primary   a Term      an Expression
4       is:     a float-literal     a Number    a Primary   a Term      an Expression
17+4    is:     Expression + Term   ->          ->          ->          an Expression

(5-1)   is:     ("("Expression")")  ->          a Primary   a Term      an Expression
5       is:     a float-literal     a Number    a Primary   a Term      an Expression
1       is:     a float-literal     a Number    a Primary   a Term      an Expression
5-1     is:     Expression + Term   ->          ->          ->          an Expression

(17+4)/(5-1) is:    Term / Primary  ->          ->          a Term      an Expression
```
### Why does the program not have a function called number()?
When the primary() function has determined that the current token is a number, the parser has reached the end of the current logic chain. It has been determined that the token is a floating-point-literal and the only remaining action is to return its value.

### What is a token?
User input interpreted as an object that can be used with the functions defined by the Calculator program.

### What is a grammar / a grammar rule?
The stipulated requirements for forming a correct expression.

### What are classes, what do we use them for?
Classes are an abstraction for creating variants of the same set of variables and functions as cohesive and re-usable units. They facilitate code organization and modularity, making it easier (In some cases at least) to build and maintain software.

### How can we provide a default value for a member of a class?
Through its contructor, either in the initializer list or in its function body (One can also simply assign a default value with the assignment operator in the class definition, but this concept has not been introduced in the book at this point).

### In the expression function, why is the default for the switch-statement to "put back" the token?
Because at that point the function is returning a result of Tokens parsed prior to the current one, and since the current token may be part of another expression it should not be discarded.

### What is look-ahead?
Reading a character from the buffer without consuming it (Ergo putting it back).

### What does putback() do and why is it useful?
See above. It is useful when we want a function further down the logic chain of the Calculator to try and use that Token / char.

### Why is the modulus operation, %, difficult to implement in the term()?
Because floating-point types don't have a built-in way to deal with modulo, you'd have to either find a library that does it or roll up your sleeves and code it yourself.

### What do we use the two data members of Token for?
To store information about sequences of characters interpreted by the Token_stream, namely their "tokenized" type and value.

### Why do we split a class's members into private and public?
To streamline its interface: Public members provide surface-level interaction while private members deal with implementation details. This restriction can also prevent inadvertent changes to the object's internal state.

### What happens in Token_stream when there's a token in the buffer and get() is called?
The Token contained in buffer gets consumed rather than feeding in more characters from std::cin into the Token_stream (The buffer is also emptied).

### Why were ';' and 'q' added to the switch-statement in get() for the Token_stream class?
To enable the user to trigger output (';') and to quit gracefully ('q').

### When should we start testing our program?
Unless creating a toy-program or under severe time-constraints: As soon as possible.

### What is a user-defined type and why would we want one?
This is more or less the same question as "What are classes, what do we use them for?" already answered above. Here's a short rehashing:  To hold data and provide useful operations on that data.

### What is the interface to a C++ user-defined type?
Again, rehashing: Public member functions and variables.

### Why do we want to rely on code libraries?
Assuming the library is robust: To save time and avoid all the pitfalls involved in development. Also, there's usually documentation and community support to tap into when something goes wrong.