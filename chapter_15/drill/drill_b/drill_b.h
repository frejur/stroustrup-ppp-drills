#ifndef DRILL_B_H
#define DRILL_B_H
#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
namespace drill {

constexpr char prompt{'>'};

inline const std::string& quit_word()
{
	static const std::string s{"exit"};
	return s;
};
inline const std::string& done_word()
{
	static const std::string s{"done"};
	return s;
};

inline void print_quit_info()
{
	std::cout << "(Enter '" << quit_word() << "' to return to the main loop)"
	          << '\n';
}

inline void print_done_or_quit_info()
{
	std::cout << "(Enter '" << done_word()
	          << "' to print the registered Persons thus far, or" << '\n'
	          << " '" << quit_word() << "' to return to the main loop)" << '\n';
}

static void hello()
{
	std::cout << "Enter a letter to continue:" << '\n'
	          << '\t' << 'a' << " Steps 1 to 4" << '\n'
	          << '\t' << 'b' << " Steps 5 to 7" << '\n'
	          << '\t' << 'c' << " Step 8" << '\n'
	          << '\t' << 'd' << " Step 9" << '\n'
	          << '\t' << 'q' << " Quit" << '\n';
}
} // namespace drill
//------------------------------------------------------------------------------

namespace step_1_to_4 {

static const std::string format()
{
	static const std::string& s{"( <Name> <Age> )"};
	return s;
}

inline const std::string info()
{
	static const std::string& s{
	    "Please input Persons using the following format: \"" + format() + "\""};
	return s;
}

struct Person
{
	std::string name;
	int age;
};

std::istream& operator>>(std::istream& is, Person& p);
std::ostream& operator<<(std::ostream& os, const Person& p);

void run();
} // namespace step_1_to_4
//------------------------------------------------------------------------------

namespace step_5_to_7 {

inline const std::string& uninit_person_name()
{
	static const std::string s{"<UNINITIALIZED>"};
	return s;
};
constexpr int uninit_person_age{0};

static const std::string& banned_chars();
constexpr int min_age{0};
constexpr int max_age{150};

void print_valid_parms();

struct Person
{
	Person()
	    : Person(uninit_person_name(), uninit_person_age){};
	Person(const std::string& name, int age)
	    : name_(valid_name(name))
	    , age_(valid_age(age)){};
	std::string name() const { return name_; };
	int age() const { return age_; };

	static const std::string& valid_name(const std::string& n);
	static int valid_age(const int a);

private:
	std::string name_;
	int age_;
};

std::istream& operator>>(std::istream& is, Person& p);
std::ostream& operator<<(std::ostream& os, const Person& p);

void run();
} // namespace step_5_to_7
//------------------------------------------------------------------------------

namespace step_8 {
void print_persons(const std::vector<step_5_to_7::Person>& v);
void run();
} // namespace step_8
//------------------------------------------------------------------------------

namespace step_9 {

static const std::string format()
{
	static const std::string& s{"( <First name> <Last name> <Age> )"};
	return s;
}

inline const std::string info()
{
	static const std::string& s{
	    "Please input Persons using the following format: \"" + format() + "\""};
	return s;
}

struct Person
{
	Person()
	    : Person(step_5_to_7::uninit_person_name(),
	             step_5_to_7::uninit_person_name(),
	             step_5_to_7::uninit_person_age){};
	Person(const std::string& first_name, const std::string& last_name, int age)
	    : fname(valid_name(first_name))
	    , lname(valid_name(last_name))
	    , age_(valid_age(age)){};
	std::string first_name() const { return fname; };
	std::string last_name() const { return lname; };
	int age() const { return age_; };

private:
	std::string fname;
	std::string lname;
	int age_;
	static const std::string& valid_name(const std::string& n)
	{
		return step_5_to_7::Person::valid_name(n);
	};
	static int valid_age(const int a)
	{
		return step_5_to_7::Person::valid_age(a);
	};
};

std::istream& operator>>(std::istream& is, Person& p);
std::ostream& operator<<(std::ostream& os, const Person& p);

void run();

} // namespace step_9

#endif // DRILL_B_H
