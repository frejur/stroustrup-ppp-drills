# Chapter 11 - Review

### The reason I/O is tricky.
1. People have their own preferences and expectations for how data should be input and output, which often require complex solutions.
2. Ideally, code should be clean, simple, maintainable and efficient.

These are competing goals, and the balancing act can be tricky.

### The function of: '<< hex'
To set the format flag to base-16, meaning integers will be formatted as hexadecimal numbers, e.g.
```
#include <iomanip>
#include <iostream>
int main() {
	std::cout << std::hex << 16 << '\n'; // prints: 10
	return 0;
}
```

### The reason for using hexidecimals in computer science.
Because the base of hexadecimal (16) is a power of 2, such numbers are well suited and often used for expressing binary data, e.g. bits.
Compared to binary it is a more compact and human-readable representation of data.
```
011001100 = 0xC4
```

### A few options often implemented for formatting integers.
There's no clear answer in the book, here are some suggestions:
- Setting the base (decimal, hex, octal, binary)
- Displaying a '+' for positive numbers.
- Leading zeros and width.
- Grouping separators (1000000 = 1,000,000)
- Hexadecimal upper/lowercase (1F vs 1f)

### The defintion of a 'manipulator'.
Terms such as 'hex' and 'oct', used to modify the state or behaviour of a stream (Mostly by setting flags).

### The prefixes for decimal, octal, hexadecimal (and binary).
```
int one        = 1;
int two        = 0b10; // binary:      0b (C++14 and later)
int eight      = 010;  // octal:       0
int thirty_two = 0x20; // hexadecimal: 0x
```

### The default format for floating-point-numbers.

### The definition of a field.

### The function of 'setpresicion()' and 'setw()'.

### The purpose of file open modes.

### Operators that 'stick' / do NOT 'stick'.
- 'hex'
- 'scientific'
- 'setprecision()'
- 'showbase'
- 'setw'

### The difference between character I/O and binary I/O.

### An example of when a binary file is probably more suitable to use than a text file.

### Two examples of when 'stringstream' is useful.

### The definition of a file position.

### The outcome of setting the file position beyond EOF.

### Situations where line-oriented input is preferred to type-specific input.

### The function of 'isalnum()'




