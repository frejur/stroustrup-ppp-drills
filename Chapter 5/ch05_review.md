# Chapter 4 Review

### Name four major types of errors and briefly define them.
1. Compile-time errors: Syntax errors, type errors...
2. Link-time errors: When the linker is unable to combine the object files into an executable.
3. Run-time errors: Errors produced by the program during use.
4. Logic errors: While types 1-3 are caught and usually bring the build process or execution to a halt, logic errors are erroneus parts of the code that sneakingly lead to unintended behaviour and sometimes incorrect results.

### What kinds of errors can we ignore in student programs?
Errors related to misbehaving hardware or system software.

### What guarantees should every completed project offer?
I should produce the desired results for all legal inputs and give reasonable error messages for all illegal inputs.

### List three approaches we can take to eliminate errors in programs and produce acceptable software.
1. We can organize the software in a way to minimize errors.
2. We can eliminate most errors though debugging and testing.
3. Finally we can make sure the remaining errors are not serious.

### Why do we hate debugging?
Debugging is tedious by nature, it's the process of patching things up rather than creating. It reminds us that we are often incapable of properly instructing the computer, and that the computer is notoriously hard to instruct.

### What is a syntax error, a type error, a logic error? Give some examples.
All of them are incorrect instructions for the compiler, but the compiler cannot catch logic errors.
```c++
/* Syntax errors - often typos or forgetting to insert punctuators */

int a = 0 // missing semicolon

for (int i=0; i < 10; ++i); // misuse of semicolon
	cout << i << endl;      // 'i' is not declared

int b = (1 + 2; // missing end parenthesis

/* Type errors - Attempting to operate on an object using incompatible object types.
				 A lot of times, because of impicit type conversions, these errors
				 are not caught by the compiler and end up being logic errors instead. */

string c() { return 'a'; } // cannot convert char to std::string
int d =  4.5 % 0.5; // incompatible operator % for floating point operands
int e { 3.33 }; 	// narrowing conversion
cout << setfill(1); // wrong character type for setfill

/* Logic errors - When the code is not doing what we thought it would. */
float f = 5/9; // integer division equals 0 not 0.555556

```

10. List four potential sources of program errors discussed in the text.

11. How do you know if a result is plausible? What techniques do you have to answer such questions?

12. Compare and contrast having the caller of a function handle a run-time error vs. the called function’s handling the run-time error.

13. Why is using exceptions a better idea than returning an “error value”?

14. How do you test if an input operation succeeded?

15. Describe the process of how exceptions are thrown and caught.

16. Why, with a vector called v, is v[v.size()] a range error? What would be the result of calling this?

17. Define pre-condition and post-condition; give an example (that is not the area() function from this chapter), preferably a computation that requires a loop.

18. When would you not test a pre-condition?

19. When would you not test a post-condition?

20. What are the steps in debugging a program?

21. Why does commenting help when debugging?

22. How does testing differ from debugging?