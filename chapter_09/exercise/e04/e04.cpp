#include <exception>
#include <iostream>;
// Chapter 9, Exercise 4

// Re-indent the "dangerously ugly code" from Chapter 8 section 4,
// explain the meaning of each construct

// Original code:
/*
struct X {
void f(int x) {
struct Y {
int f() { return 1; } int m; };
int m;
m=x; Y m2;
return f(m2.f()); }
int m; void g(int m) {
if (m) f(m+2); else {
g(m+2); }}
X() { } void m3() {
}

void main() {
X a; a.f(2);}
};
*/

struct X { // Defines struct X which contains the whole body of the code
	void f(int x) { // Defines function f
		struct Y {
			int f() { // member function with the same name as parent
				return 1;
			}
			int m; // never used
		};
		int m; // never used
		m = x; // never used
		Y m2; // instance of Y used as argument below
		return f( m2.f() ); // recursively call and return the value of function
		                    // f, passing the return value of another function
		                    // called f but this one is a member of an instance
		                    // of struct Y
	}

	int m; // never used

	void g(int m) { // function g
		if (m) {
			f(m+2); // would call f() and recursively call itself into oblivion
		} else {
			g(m+2); // recursively calls itself
		}
	}

	X() {}; // empty constructor
	void m3() {}; // never used

	void main() { // not the "real main" obviously
		X a; // would create a new instance of the current struct
		a.f(2); // would call f() and recursively call itself into oblivion
	}
};


int main()
try {
	X x{};
	std::cout << "Created an instance of X, now press any key to crash" << '\n';
	std::cin.get();
	x.main();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error";
	return 2;
}
