#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include "box.h"
#include <iostream>
#include <cmath>

// Exercise 2.	Define a rounded corner Box class
//              using lines and arcs.

using LN_ST = Line_style::Line_style_type;

int main() {
    try {
        constexpr int w{ 640 };
        constexpr int h{ 480 };
        const int mid_x{
            static_cast<int>(std::round(w * 0.5))};
        const int mid_y{
            static_cast<int>(std::round(h * 0.5))};
        constexpr int pad{ 15 };

        Simple_window win{
            {10, 10}, w, h, "Box with rounded corners"
        };

        Line_style s{ LN_ST::solid, 2 };

        E02::Box b1{
            {mid_x - pad, mid_y - pad},
            {mid_x - pad - 100, mid_y - pad - 100},
            0.8 // Almost a circle
        };
        b1.set_color(Color::black);
        b1.set_style(s);
        win.attach(b1);

        E02::Box b2{
            {mid_x + pad, mid_y - pad},
            {mid_x + pad + 100, mid_y - pad - 50},
            5, E02::CrvMethod::Radius // Specify radius of 5
        };
        b2.set_color(Color::blue);
        b2.set_style(s);
        win.attach(b2);

        E02::Box b3{
            {mid_x + pad, mid_y + pad}, 50, 200,
            1 // Max roundness
        };
        b3.set_color(Color::red);
        b3.set_style(s);
        win.attach(b3);

        E02::Box b4{
            {mid_x - pad, mid_y + pad},
            {mid_x - pad - 200, mid_y + pad + 125},
            0.2 // Just a smidge
        };
        b4.set_color(Color::yellow);
        b4.set_style(s);
        win.attach(b4);

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
