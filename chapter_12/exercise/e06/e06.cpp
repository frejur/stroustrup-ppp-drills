#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"

/* Exercise 6. Write two programs:
    1. A shape that doesn't fit inside its window.
    2. A window that doesn't fit on the screen. */

int main()
{
    // Let's reverse the order of the programs...

    // 2. A window greater in size than the current resolution
    // The title bar disappears (The window is 'maximized')
    // Also the 'Next' button disappears, supposedly because it is
    // outside the visible area. So the Simple_window class has
    // been altered to place the button at the origin instead.
    Simple_window win {
        { 0, 0 },
        static_cast<int>(x_max() * 1.1),
        static_cast<int>(y_max() * 1.1),
        "A window that stretches beyond the screen borders"
    };

    Graph_lib::Text txt { {50, 50}, "This window is really big" };
    txt.set_font_size(24);
    txt.set_color(Color::black);
    win.attach(txt);

    win.wait_for_button();

    // 1. An image that is too high to fit inside the window.
    // The image gets cropped, but can be viewed in its full after
    // resizing the window
    const int ww { 640 };
    const int wh { 360 };
    win.resize(ww, wh);

    Image img { { 120, 10 }, "img/longcat.jpg"};

    win.label("A shape that stretches beyond the window borders");

    txt.set_label("This cat is really loooong");
    win.attach(img);
    win.detach(txt); // Move  text to front
    win.attach(txt);

    win.wait_for_button();
}
