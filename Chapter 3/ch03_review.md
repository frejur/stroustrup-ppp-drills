# Chapter 3 - Review

### What is meant by the term "prompt"
An interface where the user is expected to provide text input.

### Which operator do you use to read into a variable?
The extraction / input stream operator: __<<__

### Ask user to input an integer and then read it into variable "number" in two lines of code
```
std::cout << "Please enter an integer value." << std::endl;
int number = 0; std::cin >> number;
```

### What is "\n", what does it do?
The newline character adds a linebreak / moves the cursor to next line.

### What terminates input into a string?
Whitespace characters.

### What terminates input into an integer?
Any non-numerical character.

### What is an object?
A space reserved in the computer's memory to contain data.

### What is a literal
A fixed value hard-coded into the source file that can be stored in a variable or used in calculations.

### What kinds of literals are there
Each built-in type has its own kind of literal: Integer, floating point, boolean, char, string.

### What is a variable
A name mapped to a specific address / part in the computer's memory that holds a value of the given type.

### What are typical sizes for a char, an int and a double
- Char: 8 bits = 1 byte
- Integer: 32 bits = 4 bytes
- Double: 64 bits = 8 bytes

### What measures do we use for small entities in memory, such as integers and strings?
Bytes.

### Difference between = and ==?
The single = is an assignment operator that modifies the lvalue. The double == is a logical operator used for comparing the lvalue with the rvalue.

### What is a definition?
A declaration that sets aside memory for a variable.

### What is an initialization and how does it differ from an assignment?
An initilization is the process of giving a variable a value at the point of creation while an assignment modifies that value at a later point.

### What is string concatenation and how do you make it work in C++?
The process of joining strings together. Variables of the type string may be concatenated with the + operator, but there are numerous ways.

### Legal names.
```
This_little_pig // Legal: However since a leading capital letter is in use this
				//        name is frowned upon unless it's a user defined type
MiniMineMine	// Same as above
This_1_is fine  // Illegal: Cannot use spaces
latest thing    // Same as above
2_for_1_special // Illegal: Cannot start with a number
the_$12_method  // Illegal: Except for underscores non-alphanumeric characters
				// 			are not allowed
correct?		// Same as above
_this_is_ok		// Illegal: Names with leading underscores can clash with names
				//  		reserved for implementation and system entitites
number			// Legal
