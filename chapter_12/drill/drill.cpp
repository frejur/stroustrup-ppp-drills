#include "../lib/Simple_window.h"
#include "../lib/Graph.h"
#include <system_error>

int main()
{
    try
    {
        Graph_lib::Point tl{ 100, 100 };

        Simple_window win{ tl, 600, 400, "My Window" };

        Axis xa{ Axis::x, Point{ 20, 300 }, 280, 10, "x axis" };
        win.attach(xa);

        Axis ya{ Axis::y, Point{ 20, 300 }, 280, 10, "y axis" };
        ya.set_color(Color::cyan);
        ya.label.set_color(Color::dark_red);
        win.attach(ya);

        Function sine {
            sin,
            0,
            100,
            Graph_lib::Point{ 20, 150},
            1000,
            50,50
        };

        win.attach(sine);

        win.wait_for_button();
        return 0;
    }
    catch (exception& e) {
        return 1;
    }
    catch (...) {
        return 2;
    }
}
