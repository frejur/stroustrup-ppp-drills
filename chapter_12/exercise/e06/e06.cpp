#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"

/* Exercise 6. Write two programs:
    1. A shape that doesn't fit inside its window.
    2. A window that doesn't fit on the screen. */

int main()
{
    // 1. Shape gets cropped
    Simple_window win {
        { 10, 10 }, 640, 480, "Long cat is looooooong"
    };

    Image img { {10,10}, "img/longcat.jpg"};

    win.attach(img);
    win.wait_for_button();

    // 2. Window stretches past the extents of the screen,
    // Moving it by clicking on the title bar resizes it to
    // fit on the x-axis only, the height is unaffected.
    const int ww { x_max() + 500 };
    const int wh { y_max() + 500 };

    win.resize(ww, wh);
    win.wait_for_button();
}
