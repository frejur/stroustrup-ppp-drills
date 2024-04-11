# Chapter 11 - Review

### The reason I/O is tricky.
1. Programs are made to serve humans. People have their own preferences and expectations for how data should be input and output, which often require complex solutions.
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
Because the base of hexadecimal (16) is a power of 2 such numbers are well suited and often used for expressing binary data, e.g. bits.

Compared to binary it is a more compact and human-readable representation of data.
```
011001100 = 0xC4
```

### A few options often implemented for formatting integers.
There's no clear answer in the book, here are some suggestions:
- Setting the base (decimal, hex, octal, binary).
- Displaying the base prefix ('0', '0x').
- Displaying a '+' for positive numbers.
- Leading zeros and width.
- Grouping separators (1000000 = 1,000,000)
- Hexadecimal upper/lowercase (1F vs 1f)

### The defintion of a 'manipulator'.
Terms such as 'std::hex', 'std::oct' and 'std::endl', used to modify the state or behaviour of a stream (Mostly by setting flags).

### The prefixes for decimal, octal, hexadecimal (and binary).
```
int one        = 1;
int two        = 0b10; // binary:      0b (C++14 and later)
int eight      = 010;  // octal:       0
int thirty_two = 0x20; // hexadecimal: 0x
```

### A brief overview of the 'defaultfloat' manipulator.
- The default format for floating-point numbers.
- The precision defaults to 6 digits. For 'defaultfloat' that means the maximum total number of digits.
- The number will be rounded to fit within that constraint if necessary (And switch between 'scientific' / 'fixed' as outlined below).
- It dynamically toggles between the 'scientific' and 'fixed' flags to output the most accurate representation.
```
double n_1 = 12345.6789;
double n_2 = 0.0000123456789;
std::cout << "fixed:      " << n_1 << '\n';
std::cout << "scientific: " << n_2 << '\n';
```
This will print:
```
fixed:      12345.7
scientific: 1.23457e-05
```

### The definition of a field.
A sequence of printable characters on the same line of output, whose total count equals a certain value.

Fields are typically used to maintain consistent spacing and to visually organize data in columns.

### The function of '<< setprecision(x)'.
To set the precision of any floating-point numbers passed to the stream to 'x' number of digits.

Depending on the stream's currently active floating-point number format this has different implications:
- 'defaultfloat' - precision is the total number of digits (As mentioned earlier).
- 'scientific' and 'fixed' - precision is the number of digits after the decimal point.

### The function of '<< setw(x)'.
Attemps to horizontally align the next output statement by adding fill characters until the total character count reaches 'x'.

(The default alignment and fill character is 'right-aligned' and ' ' respectively).

### The purpose of file open modes.
To control the read/write mode, initial placement of the file position, and whether existing file contents should be kept or truncated.

While mainly used to switch between character-based and binary read/write modes, there are other modes that can be useful such as appending to a file when logging stuff.

However, it's generally a good idea to use the defaults for 'ifstream' and 'ofstream' by not specifying a mode upon initilization.

### Manipulators that 'stick' / do NOT 'stick'.
Sticky:
- 'hex'
- 'scientific'
- 'setprecision()'
- 'showbase'

Not sticky (Only applies to the next input/output statement):
- 'setw()'

### The difference between character I/O and binary I/O.
I/O deals with streams of data.
- Binary I/O reads and writes raw bytes of data, any interpretation of that data is up to the developer to implement.
- Character I/O provides an abstraction layer to work with text, where the bytes are interpreted as characters.

### An example of when a binary file is probably more suitable to use than a text file.
Anything that is not text, such as an image file, which is basically a 'bag of bits'.

### Two examples of when 'stringstream' is useful.
```
int main()
{
	std::cout << "Please enter some words:" << '\n';

	// Use-case: extract types from a string.
	std::string s;
	std::getline(std::cin, s);
	std::stringstream iss{s};
	std::vector<std::string> words;
	for (std::string w; iss >> w; words.push_back(w)) {
	}

	// Use-case: format a string
	std::stringstream oss;
	oss << "The result is:" << std::setw(10) << words.size();
	print_words(words, oss.str()); // Prints label (second parameter), followed
	                               // by strings in vector (first parameter)

	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();

	return 0;
}
```

### The definition of a file position.
The specific location in a file where the next read or write operation will occur.

### The outcome of setting the file position beyond EOF.
Undefined behaviour, ergo inconsistent and unreliable results.

### Situations where line-oriented input is preferred to type-specific input.
Anytime a single line of text is also a command, or when it makes sense to compartmentalize data that way.
- Text-based games.
- CSV-files.

It can also be used to get 'raw' input (including whitespace), and perform intermediary modifications before the final extraction of types. This is demonstrated in the 'Punct_stream' class at the end of the chapter.

The authors of the book seem to prefer stream-based input.

### The function of 'isalnum(c)'
Returns 'true' when the given character 'c' is an upper or lowercase letter, or a decimal digit.




