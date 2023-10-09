#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include <iostream>
#include "arc.h"
#include <cmath>

// Exercise 1.	Define a class Arc using fl_arc(),
//				draw some demo Arcs.

int main() {
    try {
        constexpr int w{ 640 };
        constexpr int h{ 480 };
        const int mid_x{
            static_cast<int>(std::round(w * 0.5))};
        const int mid_y{
            static_cast<int>(std::round(h * 0.5))};
        constexpr int r{ 200 };
        Simple_window win{
            {100, 100}, 640, 480,
            "Drawing partial ellipses" };

        E01::Arc a{
            {mid_x, mid_y}, {mid_x + r, mid_y - r}, true};
        a.set_color(Color::black);
        win.attach(a);

        E01::Arc b{
            {mid_x + 2, mid_y},
            {mid_x + static_cast<int>(r * 0.7), mid_y + r},
            true
        };
        b.set_color(Color::red);
        win.attach(b);

        E01::Arc c{
            {mid_x + 4, mid_y},
            {mid_x - r, mid_y + r}
        };
        c.set_color(Color::green);
        win.attach(c);

        E01::Arc d{
            {mid_x + 6, mid_y},
            {
                mid_x - static_cast<int>(r * 1.25),
                mid_y - static_cast<int>(r * 0.55)
            },
            true
        };
        d.set_color(Color::blue);
        win.attach(d);
        win.wait_for_button();
    }
    catch (exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error\n";
        return 2;
    }
    return 0;
}
