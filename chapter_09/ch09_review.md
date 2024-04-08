# Chapter 9 - Review

### The two parts that make up a class.
- Representation - A data structure that represents the object's current state.
- Operations - A set of functions that can used to interact with the object, usually to view or modify its state.

### The difference between a class's interface and implementation.
- The interface is the part of the class available for direct access (public).
- The implementation is the part of the class only available indirectly through above mentioned interface (private).

### The limitations and problems of the original 'Date' struct introduced in the book.
There is no interface in place, this makes any interaction with the object tedious and error-prone. Also, exposing the internal representation of a class often leads to inadvertent modifications.

### Why the 'Date' type uses a constructor instead of the 'init_day()' function.
A constructor is guaranteed to run every time a new instance of 'Date' is created and can be used to ensure proper initialization.

### The definition of an 'invariant'. Provide examples.
- A set of integral conditions or constraints that must be preserved throughout an object's lifetime for it to be valid.

**Examples:**
```
Rectangle      Length and width must be > 0.
               Number of corners must be 4.

Bank account   Balance must be > 0.

Date object    Month must be in the range 1 - 12.
               Must have a valid day and year number.
               "Must represent a day in the past, present or future"
```

### Inline member functions, when and why?
Only when the function is short (One or two expressions) and the performance boost is needed.

The performance boost consists of the compiler replacing each call to the function with the actual body of the function. This reduces overhead related to the call stack.

However, large functions don't benefit from inlining and make the class declaration harder to read.

Also, it can increase compilation times as any changes to an inline member function changes the class definition, and will force a recompilation of all instances of that class being used.

### Why / when to use operator overloading. Provide examples.
To provide **conventional** notation for User Defined Types.
```
class Vector2d {
 /* stuff, including operator overload */
}


int main() {
	Vector2d a{1, 2};
	Vector2d b{3, 4};
	Vector2d result{a + b}; // {4, 6}
	
	bool eq = (a == b); // false
	
	std::cout << "The result is: " << result << '\n';
	// prints: "The result is: (4, 6)"
	
	return 0;
}
```

### The reason a class's public interface should be kept minimal.
By keeping the interface small but complete, learning how to use it is easier, the implementation is smoother, and maintenance / debugging is simpler.

### The effects of adding 'const' to a member function.
The 'const' classifier signals that the member function is non-modifying: it cannot change the state of the object.

### The reason 'helper functions' should be kept separate from class definitions.
- Because ideally we want to craft minimal interfaces and exclude non-critical operations (See earlier question).
- To prevent direct data corruption and avoid having to change the helper functions every time the internal representation of the class changes.
