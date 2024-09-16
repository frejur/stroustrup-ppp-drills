#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

// Exercise 15
// Define class 'Iterator', containing pure virtual function 'double* next()'.
// From the above, derive 'Vector_iterator' and 'List_iterator':
// - Initialize with a reference to either a vector<double> or list<double>.
// - next() initially returns a pointer to the 1st element of the vector / list.
// - next() then returns a pointer to the next element of the vector / list.
// - next() return 0 if there is no (next) element.
//
// Test both subclasses using function print(Iterator&) to print the elements
// of a vector<double> and a vector<list>.
//------------------------------------------------------------------------------

class Iterator
{
public:
	virtual const double* next() = 0;
};

class Vector_iterator : public Iterator
{
public:
	Vector_iterator(std::vector<double>& vv)
	    : v(vv){};
	virtual const double* next() override
	{
		if (i < v.size()) {
			return &v[i++];
		}
		return 0;
	}

private:
	std::vector<double>& v;
	int i{0};
};

class List_iterator : public Iterator
{
public:
	List_iterator(std::list<double>& ll)
	    : l(ll)
	    , i(ll.begin()){};
	virtual const double* next() override
	{
		if (l.size() && i != l.end()) {
			return &(*i++);
		}
		return 0;
	}

private:
	std::list<double>& l;
	std::list<double>::iterator i;
};

//------------------------------------------------------------------------------

void print(Iterator& iter, const std::string& text = "")
{
	if (text.size() > 0) {
		std::cout << "Printing " << text << ":\n";
	}
	int col = 0;
	while (const double* d = iter.next()) {
		std::cout << *d << '\t';
		if (++col == 5) {
			std::cout << '\n';
			col = 0;
		}
	}
}

void e15()
{
	std::vector<double> v_empty{};
	std::vector<double> v{1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};

	Vector_iterator v_iter_empty{v_empty};
	Vector_iterator v_iter{v};
	print(v_iter_empty, "empty vector");
	print(v_iter, "vector of doubles");

	std::list<double> l_empty{};
	std::list<double> l{2.0, 1.9, 1.8, 1.7, 1.6, 1.5, 1.4, 1.3, 1.2, 1.1};

	List_iterator l_iter_empty{l_empty};
	List_iterator l_iter{l};
	print(l_iter_empty, "empty list");
	print(l_iter, "list of doubles");
}

int main() {
	try {
		e15();
		std::cout << '\n' << "Press <ENTER> to exit" << '\n';
		std::cin.get();

		return 0;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
