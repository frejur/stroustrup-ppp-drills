#include "../../lib/Window.h"
#include "../../lib/Graph.h"

/* Exercise 5. Draw a red frame around a rectangle that is
 * 75% of the height of your screen and 2/3 the width */

int main()
{
    const int rw { static_cast<int>(Fl::w() * 2 / 3.0)};
    const int rh { static_cast<int>(Fl::h() * 0.75 )};
    const int border { 10 };
    const int ww { rw + 2 * border };
    const int wh { rh + 2 * border };
    Graph_lib::Window win {
        {10, 50},
        ww,
        wh,
        "A rectangle whose size is relative to the resolution of the screen"
    };

    Graph_lib::Rectangle bg { { 0, 0 }, ww, wh };
    bg.set_fill_color(Graph_lib::Color::dark_red);

    Graph_lib::Rectangle r { { border, border }, rw, rh };
    r.set_fill_color(Graph_lib::Color::dark_green);
    r.set_color(Graph_lib::Color::invisible);

    win.attach(bg);
    win.attach(r);
    return Fl::run();
}
