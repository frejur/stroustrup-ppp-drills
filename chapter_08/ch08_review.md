# Chapter 8 - Review

### The difference between a declaration / definition.
A declaration informs the compiler of the existence of an object and its type (Its interface).

A definition reserves a spot in memory for the given object and fills that space with data (The implementation).

A definition cannot exist without the other, a declaration can.

### How to syntactically distinguish the definition of a function from its declaration.
The definition must contain a function body wrapped in curly braces, even if empty.

### How to syntactically distinguish the definition of a variable from its declaration.
The variable in a definition must be assigned a value through either initialization list syntax or with the assignment operator:
```
bool is_true{true}; // List initilization
int a;              // Definition
a = 1;              // Assignment
double b = 1.337;   // Declare and define
```

### The reason why, in the Calculator program from the prev. chapter, the functions need to be declared prior to using them.
Functions need to be forward-declared whenever they are called **before** they have been defined.

E.g. __expression()__ calls __term()__ which calls __primary()__ which calls __expression()__ again.

In such cyclic calling patterns, forward declarations become necessary to ensure that functions can be called and resolved correctly.

### Is 'int a;' a definition or just a declaration?
Just a declaration, unless it is declared in the global namespace. In that case, the variable is zero-initialized, and thusly considered a definition.

### Why initilializing variables as they are declared is good practise.
At least for built-in types, accessing the value of an uninitialized variable is undefined behaviour, resulting in unpredictable results, often garbage values.

### The anatomy of a function declaration.
(Additional keyword(s) such as 'static' or 'constexpr').
Return type or 'void'.
The name of the function.
Function arguments wrapped in parentheses.
(Additional keyword(s) such as 'const' for member functions).
Semi-colon.

### The reason for indentation.
It improves legibility, mainly by indicating scope.

### The purpose of header files.
Declaring interfaces, types functions and constants that can be shared across multiple source files.
The pre-processor inserts these declarations into source files before compiling (Using #include directives).

### What is the scope of a declaration?
The context in which a declared object may exist and is accessible, e.g. block, namespace, function, etc.

### Examples of different types of scope
```
int global; // Global scope

void glob_f() {}      // File scope (Translation unit scope)
static int f_var = 0; // Also file scope

namespace ns { int hel = 10; } // Namespace scope
void params(int p) {
	// p is within the scope of function params
	
	std::cout << ns::hel << '\n'; // Accessing namespace var

	int local_a = 20; // Local scope
	{
		int local_b = 30; // Nested local scope
		
		for (int i = 0; i < 10; ++i) {
			int j = i % 3;
			// i and j only exist inside this Statement scope
			std::cout << i + j << ", ";
		}
		std::cout << '\n';
	}
	// local_b is not accessible here
	std::cout << local_a << '\n';
}

class My_class {
public:
	int m_var; // Class or struct scope

	void m_fn() {
		// member function scope
	}
};

```

### Difference between class and local scope.
- Class scope refers to variables and functions declared within a class / struct.
- Local scope refers to variables declared within a function or block (Functions cannot be nested, 'lambdas' have not been covered in the book so far).
- Class members can be accessed through instances of a class throughout the lifetime of a program.
- Locally scoped variables and functions may only be accessed within their respective blocks.

### The reason global variables should be avoided.
- Since a global variable may be modified by any part of the program, it often leads to unintended interactions between different components.
- It often leads to name clashes, causing unexpected behaviour, and making it difficult to come up with unique and meaningful variable names.
- Maintainability suffers, debugging is a pain. It's just hard to keep track of where and how global variables get modified, exspecially in larger projects.
- (It can cause issues when running Unit Tests or dealing with Concurrency)

### The difference between pass-by-value and pass-by-reference.
Pass-by-value will create a separate copy of the given object and pass it along, while pass-by-reference only forwards the original object's address in memory.

### The difference between pass-by-reference and pass-by-const-reference.
One cannot modify an object that has been passed by const-reference.

### What's swap()?
A function that upon completion and in the scope it was called in, will have swapped the values of the two objects supplied as parameters.

### Would you ever define a function with a std::vector\<double>-by-value parameter?
Yes, to indicate that the creation of a copy of said vector is somehow required anyway, usually to return a slightly altered version of the input vector without altering the original.

###  Why is undefined order of evaluation a problem? Provide examples.
As with any sort of undefined behaviour, because you can't rely on the results being consistent. In this case different systems, compilers, and optimizer settings may produce different results.
```
/* Undefined order of evaluation:
 * Don't read from / write to the same variable more than once in the same
 * expression if its value is being changed. */
 
v[i] = ++i;
v[++i] = i;
int x = ++i + ++i;
std::cout << ++i << '' << i << '\n';
fn(++i, ++i);
```

### Explain 'x&&y' and 'x||y'
Both are logical expressions, they test for truth values:
- && is the logical AND operator: If both object x and y evaluate to true, the result is also true.
- || is the logical OR operator: If either object evaluates to true, so does the result.

### The following conform / do NOT conform to C++ standards.
1. Functions within functions - Does **NOT** conform to standard C++. The exception being lambdas, which have not been covered in the book so far.
2. Functions within classes - Conforms to standard C++. Functions within classes, aka member functions, aka methods.
3. Classes within classes - Conforms to standard C++. However, the ideal is to keep classes small and simple and the book claims nested classes are useful only in "complicated classes".
4. Classes within functions - Does **NOT** conform standard C++. A class can be defined inside a function body, but it is usually a sign the function should be refactored into smaller units.

### The anatomy of an activation record.
- A copy of the called function's parameters and local variables.
- "Implementation stuff": information related to the function's caller, and necessary for the function to execute and return to its caller, sometimes with a return value or return object.

### The definition and purpose of a call stack.
A runtime data structure containing activation records, used by a program to manage function calls.
The stack ensures the correct order of execution, and proper function return.
It follows the "last in first out" principle, meaning the most recent function call is always at the top of the stack and is always the first one to be processed.

### The purpose of namespaces.
- To prevent conflicts between names used in different parts of a program (Name clashes).
- When applicable, to improve code organization by splitting it into separate units.

### The difference between a namespace / a class.
A namespace can be used to organize code without also defining a type.

### The definition of a 'using' declaration.
A way for the user to define an alternative name (usually a shorthand) for a namespace, class, or a specific member of a namespace or class.

### Why having 'using \<namespace>' declarations in headers are a bad idea.
- Namespace pollution - Every source file that includes a header containing a 'using \<namespace>' declaration will bring all names from that namespace into the current scope, potentially causing name clashes.
- Poor readability and maintainability - By invisibly obscuring the origin of names for any source file that includes it, over time, unwanted side-effect will crop up unexpectedly.

### The definition of namespace 'std'.
The namespace used to encapsulate all the standard C++ library components (functions, classes, constants, etc.).
