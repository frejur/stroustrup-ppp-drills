#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"

/* Exercise 1. Draw a rectangle as a Rectangle and as a Polygon.
 * Make the lines of the Polygon red and the lines of the
 * Rectangle blue. */

int main()
{
    Simple_window win{ {100, 100}, 640, 480, "Rectangles" };

    int dim = 100;
    int pad = 100;
    Graph_lib::Point top_left{ static_cast<int>((640 - dim * 2 - pad) * 0.5), 200 };
    Graph_lib::Rectangle rect{ top_left, {top_left.x + dim, top_left.y + dim} };
    Graph_lib::Polygon poly{
        {top_left.x + dim + pad, top_left.y},
        {top_left.x + dim + pad + dim, top_left.y},
        {top_left.x + dim + pad + dim, top_left.y + dim},
        {top_left.x + dim + pad, top_left.y + dim}
    };

    rect.set_color(Color::red);
    poly.set_color(Color::blue);

    win.attach(rect);
    win.attach(poly);
    win.wait_for_button();
}
