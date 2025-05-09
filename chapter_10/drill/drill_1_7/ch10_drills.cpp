#include "../../lib/std_lib_facilities.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <algorithm>

/*
1. Define a Point type with x and y coordinates.

2. Prompt the user for seven (x, y) pairs and store them in a vector<Point>
   called original_points.

3. Print the contents of original_points.

4. Output each point to mydata.txt using an ofstream.

5. Close the ofstream, open an ifstream for mydata.txt, and read the data into
   a new vector<Point> called processed_points.

6. Print the contents of both vectors.

7. If the vectors differ in size or values, print "Something's wrong!".
*/

constexpr int points_list_size{ 2 };
const std::string points_file_name{ "points.txt" };

struct Point {
	float x, y; // coordinates
};

Point get_point(std::istream& in);

vector<Point> get_x_number_of_points(int size);

void write_points_to_file
(   const vector<Point>& points,
	std::string filename
);

vector<Point> get_points_from_file
(   std::string filename );

void compare_points
(   const vector<Point>& vector_a,
	const vector<Point>& vector_b
);

void pad_string
(   std::string& str,
	const size_t num,
	const char paddingChar
);

// -------------------------------------------------------------

int main() {
	try
	{
		std::cout << "Please enter a total of "
				  << points_list_size << " (x, y) pairs\n";

		// store valid points
		auto original_points = get_x_number_of_points(
											  points_list_size);

		std::cout << "\nSuccessfully added "
				  << points_list_size << " points:\n";
		std::cout << "------------------------------\n";
		for (Point pt : original_points)
			std::cout << "\t(" << pt.x << ", " << pt.y << ")\n";

		// Write points to .txt
		write_points_to_file(original_points, points_file_name);

		auto file_points = get_points_from_file(points_file_name);

		std::cout << "\nReading from file:\n";
		std::cout << "------------------------------\n";
		for (Point pt : file_points)
			std::cout << "\t(" << pt.x << ", " << pt.y << ")\n";

		std::cout << "Standard Compare:\n";
		compare_points(original_points, file_points);

		std::cout << "Compare Data with differing values:\n";
		// original_points[0].x += 2.3; // test change
		// file_points.push_back(Point{ 2.3,5.4 }); // test add
		compare_points(original_points, file_points);

		keep_window_open();

		return 0;
	}
	catch (const std::runtime_error& re)
	{
		std::cerr << "Runtime Error: " << re.what() << '\n';
		throw;
	}
	catch (const std::invalid_argument& ae)
	{
		std::cerr << "Invalid argument: " << ae.what() << '\n';
		throw;
	}
}

// -------------------------------------------------------------

Point get_point(std::istream& in)
{
	char c;
	in >> c;
	if (c != '(')
		throw std::runtime_error(
			"Invalid syntax, expected starting "
			"parentheses.");

	float x;
	if (!(in >> x))
		throw std::runtime_error(
			"Invalid syntax, expected floating "
			"point value.");

	in >> c;
	if (c != ',')
		throw std::runtime_error(
			"Invalid syntax, expected comma.");

	float y;
	if (!(in >> y))
		throw std::runtime_error(
			"Invalid syntax, expected floating "
			"point value.");

	in >> c;
	if (c != ')')
		throw std::runtime_error(
			"Invalid syntax, expected "
			"end parentheses.");

	return Point{ x,y };
}

vector<Point> get_x_number_of_points(int size)
{
	vector<Point> points;

	if (size <= 0)
		throw std::invalid_argument(
			"Size has to be at least 1.");

	while (points.size() < size)
	{
		points.push_back(get_point(std::cin));
	}
	return points;
}

// -------------------------------------------------------------

void write_points_to_file(const vector<Point>& points,
						  std::string filename)
{
	if (points.size() < 1)
		throw std::invalid_argument("Empty points vector.");
	std::ofstream ost{ filename };
	if (!ost) throw std::runtime_error("Cannot open file.");

	// assumes all entries are valid
	for (Point pt : points)
		ost << '(' << pt.x << ',' << pt.y << ')' << '\n';

	std::cout << "Succesfully wrote " << points.size()
		<< " point entries into '"
		<< filename << "'\n";
}

vector<Point> get_points_from_file(std::string filename)
{
	vector<Point> points;

	std::ifstream ist{ filename };
	if (!ist) throw std::runtime_error("Cannot open file.");

	char c;
	while (!ist.eof()) {
		points.push_back(get_point(ist));
		ist >> std::ws; // eat whitespace
	}

	return points;
}

void compare_points(const vector<Point>& vector_a,
					const vector<Point>& vector_b)
{
	std::size_t n = std::max(vector_a.size(),
							 vector_b.size());
	if (n < 1) throw std::runtime_error("Zero length data");

	const std::string missing = "N/A\t\t";

	std::cout << "\nComparing Data:\n";
	std::cout << "----------------------------------"
			  << "----------------------------------\n";
	std::cout << "#   | CONSOLE\t\t\t| FILE\t\t\t| COMMENT\n";
	std::cout << "=================================="
			  << "==================================\n";

	for (int i = 0; i < n; ++i) {
		std::string comment = "";
		std::string idx = std::to_string(i);
		std::string a="", b="";
		pad_string(idx, 3, '0');

		if (vector_a.size() > i)
		{
			a = std::to_string(vector_a[i].x) + ", " +
				std::to_string(vector_a[i].y);
		}
		else
			a = missing;
		if (vector_b.size() > i)
		{
			b = std::to_string(vector_b[i].x) + ", " +
				std::to_string(vector_b[i].y);
		}
		else
			b = missing;

		if (a == missing || b == missing)
			comment = "MISSING";
		else if (vector_a[i].x == vector_b[i].x &&
				 vector_a[i].y == vector_b[i].y)
			comment = "SAME";
		else
			comment = "DIFFERENT";

		std::cout << idx << " | "
				  << a << "\t| " << b << "\t| "
				  << comment << '\n';
	}
}

void pad_string(std::string& str, const size_t num,
				const char paddingChar = ' ')
{
	if (num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}
