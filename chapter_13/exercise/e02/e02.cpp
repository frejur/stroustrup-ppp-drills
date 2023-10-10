#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include <iostream>
#include <cmath>

// Exercise 2.	Define a rounded corner Box class
//              using lines and arcs.

int main() {
    try {
        constexpr int w{ 640 };
        constexpr int h{ 480 };
        const int mid_x{
            static_cast<int>(std::round(w * 0.5))};
        const int mid_y{
            static_cast<int>(std::round(h * 0.5))};

    Simple_window win{
        {10, 10}, w, h, "Box with rounded corners"};

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
