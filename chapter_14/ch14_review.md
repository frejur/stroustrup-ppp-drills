
# Chapter 14 - Review

### The definition of an application domain.
The conceptual field or area in which the program is expected to run and function.

### The ideals for naming when designing a library
Generally speaking:
- Clarity
- Consistency
- Precision

Pertaining to classes:
- Chose names that describe different roles or concepts inside of the given **application domain**.
- Also choose names that convey how the classes are related in terms of hierarchy.
- Distinguish more **concrete objects** (e.g. *Rectangle*) from **abstract objects** (e.g. *Shape*).

Regarding member functions:
- The name should accurately describe the operation performed.
- Functions that perform similar operations in different classes should have the same name.
- Functions that appear similar on the surface but behave differently should be distinguished through more precise naming.
- The name should reflect whether an operation results in a copy or a reference (*Shape.add()* vs *Window.attach()*).

### Things that can be named
- Classes
- Methods
- Data members
- Parameters

### The services offered by the 'Shape' type

The *Shape* class is the base class for graphical objects drawn inside a window.
- It serves as an abstract container for all derived graphical objects
- It provides a common interface for these objects.
- It implements fundamental operations necessary for these objects.

Key functionalities include:
- Attaching a graphical object to a Window, which interfaces with the operating system and physical screen.
- Managing colors, line styles, and other drawing instructions.
- Enabling the shape to be drawn based on its properties.

### The difference between an abstract and a concrete class
According to the book, a class is *abstract* if it can only be used as a base class:
- It's not possible to create a direct instance of an abstract class.
- Only concrete classes, including those who inherit from abstract classes, can be used to create objects.

Formally a class is abstract only if it contains at least one pure virtual function.

### Ways to make a class abstract
If *making abstract* means preventing direct instantiation of a class (See the answer above), one can do this by either:
1. Making all of its constructors *protected*.
2. Defining at least one pure virtual function.

```c++
#include <iostream>

/* Prevent instantiation of base class

   Method 1:  Protected constructors */
class Base_1
{
protected:
	Base_1(){};
};

/* Method 2: Define at least one pure virtual function */
class Base_2
{
public:
	virtual void pvf() = 0;
	virtual void pvf2() = 0;
};
/*          Or leave at least one pure virtual function NOT overriden */
class Base_3 : public Base_2
{
public:
	virtual void pvf()
	{
		std::cout << "Base_3::"
		          << "pvf()" << '\n';
	};
};
/* HOWEVER: After overriding all of the pure virtual functions,
 *          the class may be initiated */
class Base_4 : public Base_2
{
public:
	virtual void pvf()
	{
		std::cout << "Base_4::"
		          << "pvf()" << '\n';
	};
	virtual void pvf2()
	{
		std::cout << "Base_4::"
		          << "pvf2()" << '\n';
	};
};

int main()
{
	// Base_1 b1; // Compile time error: Calling a protected constructor
	// Base_2 b2; // Compile time error: Variable type is an abstract class
	// Base_3 b3; // Compile time error: Variable type is an abstract class
	Base_4 b4; // Works
	b4.pvf();
	b4.pvf2();

	return 0;
}
```
	
### Controlling access to class members
Through declaring data members and methods as public, private or protected, it is possible to control their visibility and accessibility.

Access control is often used to protect the internal representation of a class, while regulating any interactions with the class through a controlled interface.

### The befits of making a data member private
- Protects against modifications of that member other than through the class interface.
- Prevents derived classes from accessing that member outside of the interface defined in the base class (Unlike *protected* members).
- Reduces overall complexity by only exposing the necessary functionality.
- Enhances flexibility by allowing changes to internal implementations without affecting external code. 

### The definition of a virtual function
A function that allows derived classes to override it, enabling type-dependent implementations of the same function, and with the correct implementation being chosen at runtime depending on the actual object type of the caller (Polymorphism).

### The difference between virtual and a non-virtual function
Regular function calls are resolved at compile-time depending on the type of pointer or reference of the caller. Defining a non-virtual function with the same *signature* as an existing function in a superclass **hides** that function rather than override it.
```c++
#include <iostream>

class Base
{
public:
	void f() { std::cout << "Base::f()" << '\n'; };
	virtual void vf() { std::cout << "Base::vf()" << '\n'; };
};

class Ext : public Base
{
public:
	void f() { std::cout << "Ext::f()" << '\n'; };
	void vf() { std::cout << "Ext::vf()" << '\n'; };
};

int main()
{
	Ext e;
	Base& b = e;
	b.f(); /* Because f() is not a virtual function, the compiler resolves
	          the object to be of type 'Base' and prints the version
	          of f() found in 'Base'. */

	b.vf(); /* Because vf() is a virtual function, the program determines that
	           b is an object of type 'Ext' at run-time, and calls the vf() found
	           in 'Ext' */
	return 0;
}
```

### The definition of a 'base class'
A class that provides a common interface and fundamental facilities for the classes that derive from it.

### The key characteristics of a 'derived class'
- Inherits properties and methods of the base class
- Extends the base class's functionality through new attributes or methods.

### The definition of 'object layout'
Describes how an object's data members, including inherited ones, are laid out in memory.

This structure may include its own virtual table pointer (vptr) pointing to a virtual table (vtbl).

### The reason why object layout details are relevant / important
Such details, though crucial for low-level programming and optimization, are mainly brought up to increase understanding for virtual functions, and dispel myths about their cost.

### Methods for making a class easier to test

**Interface inheritance and virtual functions**:
Since testing usually builds on top of existing code, and involves a fair amount of tweaking back and forth, being able to extend the system without modifying it is extremely useful.

**Encapsulation**:
Keep implementation details private to protect them from direct use, making it easier to test overall behavior without messing with implementation details.

**Separation of concerns**:
Split up the application domain into logical concepts, use abstractions if needed. Given the gargantuan task that is testing, it will be very beneficial to be able to break things down into smaller pieces.

**Write clear and consistent interfaces**:
If the code is easy to read and use it is also easier to test.

### The utility of an inheritance diagram
It helps visualize groups of classes by providing an overview of their inheritance relationships.

### The difference between a 'protected' and a 'private' member
- **private** - Directly accessible only within the class that defines it, not within derived classes.
- **protected** - Directly accessible within the class that defines it and within derived classes.

Neither is accessible to external code (Other than through some kind of interface).

### The members of a base class accessible to classes derived from it
Members made 'public' or 'protected' in the base class.

### The difference between a pure virtual function and a regular virtual function
- **Pure Virtual Function**: Defines an interface without implementation, makes the class abstract.
- **Regular Virtual Function**: Defines a default implementation that can be overridden.

Unlike regular virtual functions, the presence of any pure virtual functions in a class definition will prevent the instantiation of such an object at compile time.

### Reasons for making a member function virtual
To allow derived classes to provide their own implementation and the program to chose to call the correct implementation depending on the type of object that calls it in run-time. (**Dynamic Dispatch**)

### Reasons for making a virtual member function pure?
- To create a function whose implementation must be defined in a class derived from the base class.
- To create an abstract class that cannot be initiated itself.
Classes with pure virtual functions tend to be 'pure interfaces', ergo they have no data members or constructors and rely entirely on derived classes for their implementations.

### The meaning of overriding
To define a new implementation for a virtual function in a derived class.

### The difference between interface inheritance and implementation inheritance
- **Interface inheritance** - Provides a sort of contract for derived classes to follow: A well-designed object of a derived class should be able to be used as an object of its public base class.
- **Implementation inheritance** - Allows derived classes to reuse and extend the base class.

### The definition of object-oriented programming
A programming paradigm that structures code using abstractions known as *objects*.

Objects combine data and methods, and support **inheritance**, **encapsulation**, and **run-time polymorphism**.
