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
All of them are faulty instructions, but the compiler cannot catch logic errors.
```c++
/* Syntax errors - often typos or forgetting to insert punctuators */

int a = 0: // colon instead of semicolon

for (int i=0; i < 10; ++i); // misuse of semicolon, logic error but also:
    cout << i << endl;      // syntax error, 'i' is not declared

int b = (1 + 2; // missing end parenthesis

/* Type errors - Attempting to operate on an object using incompatible object types.
                 A lot of times, because of implicit type conversions, these errors
                 are not caught by the compiler and end up being logic errors instead. */

string c() { return 'a'; } // cannot convert char to std::string
float d =  4.5 % 0.5;   // incompatible operator % for floating point operands
int e { 3.33 };         // narrowing conversion
cout << setfill(1);     // wrong character type for setfill

/* Logic errors - AKA semantic errors. When the code is not doing what we thought it would. */
float f = 5/9;      // integer division: equals 0 not 0.555556
char e = "1\t2"[3]; // '\t' counts as one character,
                    // an index of 3 is out of bounds = undefined behaviour
for (unsigned int count{ 10 }; count >= 0; --count) cout << count; // infinite loop
```

### List four potential sources of program errors discussed in the text.
1. Poor Specification - Not knowing the details of the intended functionality will lead to unexpected behaviour
2. Incomplete programs - Parts of a program can often be left half-finished
3. Unexpected Arguments and Input
4. Unexpected state - Incorrect or incomplete data

### How do you know if a result is plausible? What techniques do you have to answer such questions?
Usually you don't know, you estimate. It can be helpful to scribble things down on a piece of paper, or try to find references online.

### Compare and contrast having the caller of a function handle a run-time error vs. the called function’s handling the run-time error.
Caller error handling is specific to the context in which it is run, callee error handling can be re-used in multiple contexts and its definition can be updated.

### Exceptions rather than "error messages", why?
If the callee just returns an error message, that's really the end of that error. If instead the callee throws an exception the caller can catch it and take action depending on the type of error and the state of the caller.

### How do you test if an input operation succeeded?
If using iostreams:
```c++
while (cin) // the state of cin is true until not successful
```

### Describe the process of how exceptions are thrown and caught.
1. The part of the code that may throw an error is wrapped inside a try block
2. If any element within this block throws an exception, this is caught by catch blocks defined in immediate conjunction with the try block.
3. The catch clauses catch different exception types.
4. The content of the catch block defines the action to take depending on the nature of the exception. 

### Why is accessing an element from vector v with v[v.size()] a range error? What would be the result?
Since the [] operator uses 0-based indexing v[v.size] attempts to fetch an element that does not exist. The result would be undefined behaviour.

### Define pre-condition and post-condition, preferably a computation that requires a loop
```c++
vector<int> fibonacci_gen(int count)
// Generates a list of fibonnaci numbers given the count
// Pre-condition: count is greater than 0
// Post-condition: size of vector is the same as count,
//                 last element is equal or greater than first element
{
    if (count < 1) throw runtime_error("Invalid argument count");
    vector<int> v {0};
    if (count>1) v.push_back(1);
    for (int i=2; i < count; ++i)
        v.push_back(v[i-2] + v[i-1] );
    if ( (v.size() != count) ||
         (v.front() > v.back()) )
        throw runtime_error("Incorrect size / last element is not equal or greater than first");
    return v;
}
```

### When would you not test a pre-condition?


19. When would you not test a post-condition?

20. What are the steps in debugging a program?

21. Why does commenting help when debugging?

22. How does testing differ from debugging?