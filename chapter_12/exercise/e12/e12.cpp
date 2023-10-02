#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"

/* Write a program that draws "starlike" patterns by
 * connecting points on a superellipse */

int main()
{
    const int ww { 640 };
    const int wh { 320 };
    Simple_window win {
        {10, 10}, ww, wh, "Superb Ellipses" };

    const int mid_x { static_cast<int>(ww / 2) };
    const int mid_y { static_cast<int>(wh / 2) };

    win.wait_for_button();

}
