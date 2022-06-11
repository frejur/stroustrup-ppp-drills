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
(17+4)  is:		("("Expression")")	->			a Primary	a Term		an Expression
17      is:		a float-literal		a Number	a Primary	a Term		an Expression
4       is:		a float-literal		a Number	a Primary	a Term		an Expression
17+4    is:		Expression + Term	->			->			->			an Expression

(5-1)   is:		("("Expression")")	->			a Primary	a Term		an Expression
5       is:		a float-literal		a Number	a Primary	a Term		an Expression
1       is:		a float-literal		a Number	a Primary	a Term		an Expression
5-1     is:		Expression + Term	->			->			->			an Expression

(17+4)/(5-1) is:	Term / Primary	->			->			a Term 		an Expression
```
### Why does the program not have a function called number()?
When the primary() function has determined that the current token is a number, the parser has reached the end of the logic chain. At that point the program will always attempt to read in a floating-point-literal.

### What is a token?

### What is a grammar / a grammar rule?

### What are classes, what do we use them for?

### How can we provide a default value for a member of a class?

### In the expression function, why is the default for the switch-statement to "put back" the token?

### What is look-ahead?

### What does putback() do and why is it useful?

### Why is the modulus operation, %, difficult to implement in the term()?

### What do we use the two data members of Token for?

### Why do we split a class's members into private and public?

### What happens in Token_stream when there's a token in the buffer and get() is called?

### Why were ';' and 'q' added to the switch-statement in get() for the Token_stream class?

### When should we start testing our program?

### What is a user-defined type and why would we want one?

### What is the interface to a C++ user-defined type?

### Why do we want to rely on code libraries?