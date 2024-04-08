# Chapter 07 - Review Questions
### What is the purpose of working on the program after the first version works? List reasons.
- To gradually improve it.
- To squash bugs.
- To experiment with new ideas.

### Why does '1+2; q' not quit the Calculator after it receives an error?
Because, the 'q' character is already consumed as the exception is thrown. This exits the current function and keeps exiting the callee functions until the exception is caught by the main loop, which restores the state of the calculation loop.

### Why was the constant character called 'number' added?
To avoid magic constants.

### main() was split into two separate functions, what does the new function do and why was it split?
Because ideally a function should perform a single logical action, main() was split up into the general task of starting / ending / handling errors (Still in main()), and handling the calculation loop (The new function called calculate())

### Why do we split code into multiple functions? State principles.
- Improves readability by naming the computation
- Improves structure by keeping parts of the computation logically separate.
- Hide implementation details behind clear interfaces.
- Enhances productivity through reuse.
- Facilitates testing and debugging.

### What's the purpose of comments and how should it be done?
Explaining things that cannot be clearly and directly said in code. Comments should be brief and to the point and leave no room for ambiguity.

### What does __narrow_cast__ do?
It converts one type to the other, throwing an exception if there's information loss.

### What's the use of symbolic constants?
- To improve legibility by naming things descriptively.
- To avoid repitition by defining a value once.
- To avoid bugs commonly introduced by the use of magic constants.

### Why care about code layout?
Well laid out code is both easier to read and maintain.

### How do we handle % of floating-point numbers?
The book presents two options:
1. Supporting it through fmod() contained in __\<cmath>__
2. Throwing an exception through the use of __narrow_cast__.

### What does __is_declared()__ do and how does it work?
It returns __true__ if the given variable already exists.
It does so by looping through the member variable __var_table__, a vector of strings, and returning __true__ when a match is found, or __false__ if the end was reached an no match was found.

### The input representation for let is more than one character. How is it accepted as a single token in the modified code?
When a letter is fed into the Token_stream, all letters (including the one just consumed) until the next whitespace are consumed as a string.
If that string is equal to __declkey__=='let', they are 'tokenized' and stored as a Token of type __let__.

### What are the rules for variable names in the calculator program?
Except for underscores not being allowed, the same as for variable naming in C++: Leading letter, body of letters and numbers.

### Why is it a good idea to build a program incrementally?
- It can reduce the feeling of being overwhelmed by breaking work into manageable chunks.
- It fosters structured code organization, thereby improving readability and maintainability.
- Establishing some form of milestones usually aids project management and collaboration (Even better: Versioning!).
- There's less risk of underestimation and scope creep when you build in stages rather than just adding new features.
- Incremental development also promotes early evaluation = delivering according to specs.

### When do you start to test?
Unless hobbyist or pressed for time - ASAP.

### When do you re-test?
For each stage, often.

### How do you decide what should be a separate function?
I think this varies a little depending on the programming language and coding style, but for this book it should be along the lines of what's already stated in one of the earlier answers:
- If it improves readability through naming or improves structure by keeping pieces of computational logic separate.
- If it can hide implementation details behind clear interfaces.
- If it can enhance productivity through reuse.
- When it facilitates testing and debugging.

### How to choose names for variables and functions? List reasons.
#### Descriptive but not wordy.
- To convey the code's intention without needing to delve into its implementation details.
- To reduce ambiguity, avoid unnecessary typing, and reduce width.

#### Avoid cryptic abbreviations, acronyms, or single-letter names
Duh.

#### Consistent naming and case(snake_case, camelCase).
To promote cohesiveness and improve legibility and navigation.

#### Avoid Reserved Words and leading underscores.
(Breaks stuff)

### Why add comments?
I don't mean to sound like a broken record, but: Explaining things that cannot be clearly and directly said in code.

### What should / should NOT be in commentst?
Sadly, ASCII art is frowned upon.

### When do we consider a program finished?
Never. But when the product has been delivered according to specs is a good rule of thumb! "When all time/money has been exhausted" is another possible answer.
