# Chapter 8, Exercise 14

## Why would you pass an argument by const value?

### Why not just pass by const reference?
Usually an object is passed by value if the intention is to modify it without affecting the original, but since the object is marked const that's not the reason here. This means that the type of the passed object probably has one or several of the below characteristics:

- Small size
- Simple structure
- Cheap copy operations
- No dynamic memory allocation
- Immutable by nature
- Identity is based solely on its value

### Why mark it const then?

For the same reason you would pass an object by const reference really: To express or enforce immutability:

- When passing literal values or expressions, making the parameter const ensures that you don't modify them by mistake.
- It can serve as a form of documentation, indicating that the function should not modify the passed parameter.
- It can help to distinguish between two functions that are similar but one doesn't modify the object.

### Examples:
```c++
void print_selected(const char c) {
	std::cout << "You have selected '" << 'c' << "'\n";
}

int validate_number(const int n) {
	// validate... throw error if not valid
	return n;
}

Record updatedRecord(const Data& d, Record d) {}
void refreshRecord(const Data& d, const Record d) {};
```