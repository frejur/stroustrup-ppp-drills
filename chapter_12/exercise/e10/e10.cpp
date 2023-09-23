#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include "arrow.h"
#include <memory>
#include <vector>
#include <math.h>

/* Exercise 10. Draw the file diagram from 12.8. */

int main()
{
    const int ww { 640 };
    const int wh { 480 };
    Simple_window win{ {100, 100}, ww, wh, "File diagram" };

    Point c { static_cast<int>(640 / 2), static_cast<int>(480 / 2) };
    const float full_c { 6.10865 };
    std::vector<std::unique_ptr<Arrow>> arrows{};
    for (unsigned int i = 0; i < 36; ++i) {
        float r { 64 + 200 * ((static_cast<float>(i) + 1) / 36) };
        std::unique_ptr<Arrow> a (
            new Arrow (
                c,
                { static_cast<int>(c.x + r * cos(full_c / 36 * (i + 1))),
                  static_cast<int>(c.y + r * sin(full_c / 36 * (i + 1))) }
                ));
        arrows.push_back(std::move(a));
    }

    for (auto &a : arrows) {
        a->set_color(Color::black);
        a->set_fill_color(Color::black);
        a->set_style(Line_style::solid);
        win.attach(*a);
    }

    win.wait_for_button();
}
