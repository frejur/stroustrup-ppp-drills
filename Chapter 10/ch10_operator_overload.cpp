#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <memory>

/*
    Rewrite Drill Excercise with I/O operator overloading
*/

namespace ch10_operator_overload
{
    constexpr int points_list_size{ 2 };
    const std::string points_file_name{ "points_2.txt" };

    class Point
    {
    private:
        float _x{ 0.0 }, _y{ 0.0 };
        bool _is_undefined{ true }; 
        const std::string _UNDEF_STR{ "NOT DEFINED" };

        std::string _get_as_string(int axis) const {
            if (_is_undefined) {
                return _UNDEF_STR;
            }
            return (axis == 0
                ? std::to_string(_x)
                : std::to_string(_y));
        }
    public:
        float getX() { return _x; }
        float getY() { return _y; }
        void setX(float x) { _x = x; }
        void setY(float y) { _y = y; }
        void set(float x, float y) { _x = x; _y = y; }

        Point() { }
        Point(float x, float y) {
            set(x, y);
            _is_undefined = false;
        }

        friend std::ostream& operator<< (std::ostream& out, const Point& point);
        friend bool operator== (const Point& a, const Point& b);
        friend bool operator!= (const Point& a, const Point& b);
    };

    std::ostream& operator<< (std::ostream& out, const Point& point)
    {
        out << point._get_as_string(0) << ", " << point._get_as_string(1);

        return out;
    }

    bool operator== (const Point& a, const Point& b) {
        return (a._x == b._x && a._y == b._y);
    }

    bool operator!= (const Point& a, const Point& b) {
        return (a._x != b._x || a._y != b._y);
    }

    const Point MISSING{}; 

    Point get_point(std::istream& in);

    std::vector<Point> get_x_number_of_points(int size);

    void write_points_to_file
    (   const std::vector<Point>& points,
        std::string filename
    );

    std::vector<Point> get_points_from_file
    (   std::string filename );

    void compare_points
    (   const std::vector<Point>& vector_a,
        const std::vector<Point>& vector_b
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
                std::cout << "\t(" << pt << ")\n";

            // Write points to .txt
            write_points_to_file(original_points, points_file_name);

            auto file_points = get_points_from_file(points_file_name);

            std::cout << "\nReading from file:\n";
            std::cout << "------------------------------\n";
            for (Point pt : file_points)
                std::cout << "\t(" << pt << ")\n";

            std::cout << "Compare:\n";
            compare_points(original_points, file_points);

            std::cout << "\n... Repeat with Mock Data ...\n";
            std::mt19937 mt;
            std::uniform_real_distribution<float> dis(0.0, 999.999);
            float random_x = dis(mt);
            original_points[0].setX(random_x); // test change
            file_points.push_back(Point{ 2.3, 5.4 }); // test add
            compare_points(original_points, file_points);
            
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

        return Point{ x, y };
    }

    std::vector<Point> get_x_number_of_points(int size)
    {
        std::vector<Point> points;

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

    void write_points_to_file(const std::vector<Point>& points,
                              std::string filename)
    {
        if (points.size() < 1)
            throw std::invalid_argument("Empty points vector.");
        std::ofstream ost{ filename };
        if (!ost) throw std::runtime_error("Cannot open file.");

        // assumes all entries are valid
        for (Point pt : points)
            ost << '(' << pt << ')' << '\n';

        std::cout << "Succesfully wrote " << points.size()
            << " point entries into '"
            << filename << "'\n";
    }

    std::vector<Point> get_points_from_file(std::string filename)
    {
        std::vector<Point> points;

        std::ifstream ist{ filename };
        if (!ist) throw std::runtime_error("Cannot open file.");

        char c;
        while (!ist.eof()) {
            points.push_back(get_point(ist));
            ist >> std::ws; // eat whitespace
        }

        return points;
    }

    void compare_points(const std::vector<Point>& vector_a,
                        const std::vector<Point>& vector_b)
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
            bool    has_a = vector_a.size() > i,
                    has_b = vector_b.size() > i;
            pad_string(idx, 3, '0');

            if (!has_a || !has_b) {
                comment = "MISSING";
            } else if (vector_a[i] == vector_b[i])
                comment = "SAME";
            else
                comment = "DIFFERENT";

            std::cout << idx << " | "
                      << (has_a ? vector_a[i] : MISSING) << "\t| "
                      << (has_b ? vector_b[i] : MISSING) << "\t| "
                      << comment << '\n';
        }
    }

    void pad_string(std::string& str, const size_t num,
                    const char paddingChar = ' ')
    {
        if (num > str.size())
            str.insert(0, num - str.size(), paddingChar);
    }
}
