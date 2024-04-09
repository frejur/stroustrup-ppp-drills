# Chapter 10 - Review

### The way most modern computers deal with the variety of in and output devices.
They separate the handling of I/O devices into device drivers, accessed through an I/O library that provides a standardized and unified interface.

As long as the interface doesn't change, this enables programs to read and write data without worrying about the specifics, and programmers to write device-independent software.

### The essential function of 'istream'.
To extract characters from an input source (console, file, etc.) and turn sequences of those characters into values of various types.

### The essential function of 'ostream'.
To turn values of various types into sequences of characters and send those characters to an output source (console, file, etc.).

### The definition of a 'file'.
A sequence of bytes numbered from 0 upward and stored to disk.

### The definition of a 'file format'.
A set of rules that specify how to interpret the bytes contained in a file.

### Four different types of devices that may require I/O.
1. Keyboard / Mouse
2. Printer / Scanner
3. Webcam / Microphone
4. Ethernet adapter / Wi-Fi card / modem.

### The four steps for reading a file.
1. Determine path to file.
2. Open for reading.
3. Read in characters.
4. Close the file (Usually done implicitly as the 'ifstream' goes out of scope)

### The four steps for writing to a file.
1. Determine path to file.
2. Open for writing
3. Write out object as characters.
4. Close the file (Usually done implicitly as the 'ofstream' goes out of scope)

### The four stream states.
1. good() - The most recent operation successful.
2. eof() - End of file / input.
3. fail() - A logical error happened, e.g. Attempted to read a value of the wrong type.
4. bad() - A serious error occured, e.g. Hardware failure or file corruption.

The distinction between fail() and bad() is usually that bad() signals that the error cannot be be recovered from.

### How to resolve: The user typing an out-of-range value.
Handle locally: Print an "error message", discard the value.

### How to resolve: Getting no value (end of file).
Abort by throwing an expection and hope that some other part of the program can cope.

### How to resolve: The user typing something of the wrong type.
Handle locally: Print an "error message", keep discarding characters until a valid type can be extracted or eof() / bad().

### How input is usually harder than output.
Generally speaking, input is very unpredictable and there is simply a lot more oppportunity for error. It usually requires extensive error checking and validation.

### How output is usually harder than input.
The book doesn't really provide a clear answer to this question, at least not at this point. Here are some possible answers:
- The task of presenting data in a user-friendly way can be very complex.
- Coming up with an appropriate output format is not a trivial task, and as the program grows, any inherent limitations of the chosen format may have significant consequences.
- While less frequent, output error can be hardware-related, which leaves the developer at the mercy of the output devices functioning as expected.

### The reason I/O is often separated from computation.
I/O is essentially used to get data into a program and to get the results back out again.

According to the principle of keeping logically distinct concerns separate, the intermediate computation step is best kept apart.

This makes code code clearer, easier to maintain and debug, and enables code reuse (of only the parts of the code that are needed) through function calls.

### The two most common uses of 'istream.clear()'.
```
std::istream is;
is.clear();                       // Open  (Set to good())
is.clear(std::ios_base::failbit); // Close (Set to fail())
/* The 'badbit' and 'eofbit' flags are usually not set manually */
```

### Boilerplate function declaration for '<<' for user-defined-type 'X'.
```
std::ostream& operators<<(std::ostream& os, const X& obj);
```

### Boilerplate function declaration for '>>' for user-defined-type 'X'.
```
std::istream& operators>>(std::istream& is, X& obj);
```
