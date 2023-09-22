#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include <memory>
#include <vector>

/* Exercise 8: Draw the Olympic rings */

std::vector<std::unique_ptr<Line>> draw_grid(const Point &o, const int rings_h, const int rings_w, const int rings_unit)
{
    std::vector<std::unique_ptr<Line>> grid_lines;
    int count {0};
    for (int r = 1; r < 16; ++r) {
        std::unique_ptr<Line> l (
            new Line (
                { o.x, o.y + r * rings_unit },
                { o.x + rings_w, o.y + r * rings_unit }
                ));
        grid_lines.push_back(std::move(l));
        ++count;
        grid_lines[count - 1]->set_color(Color::black);
    }
    for (int c = 1; c < 35; ++c) {
        std::unique_ptr<Line> l (
            new Line (
                { o.x + c * rings_unit, o.y },
                { o.x + c * rings_unit, o.y + rings_h }
                ));
        grid_lines.push_back(std::move(l));
        ++count;
        grid_lines[count - 1]->set_color(Color::black);
    }
    return grid_lines;
}

int main()
{
    const bool DRAW_GRID = false;
    const int ww { 640 };
    const int wh { 320 };
    Simple_window win { {10, 10}, ww, wh, "Olympic Rings" };

    const int mid_x { static_cast<int>(ww / 2) };
    const int mid_y { static_cast<int>(wh / 2) };

    const int rings_desired_w { 580 };
    const int rings_unit { static_cast<int>(rings_desired_w / 35) };
    const int rings_w { rings_unit * 35 };
    const int ring_d { rings_unit * 11 };
    const int ring_r { static_cast<int>(ring_d / 2)};
    const int rings_h { ring_d + 5 * rings_unit };

    Point tl {
        static_cast<int>(mid_x - rings_w / 2),
        mid_y - static_cast<int>(rings_h / 2) };


    // Grid
    if (DRAW_GRID) {
        auto grid_lines = draw_grid(tl, rings_h, rings_w, rings_unit);

        for (auto &l : grid_lines) {
            win.attach(*l);
        }
    }

    // Rings
    Circle c_blue {
        { tl.x + ring_r, tl.y + ring_r },
        ring_r - static_cast<int>(rings_unit * 0.5)};

    c_blue.set_color(Color::blue);
    c_blue.set_style(Line_style(Line_style::solid, rings_unit));

    Circle c_black {
        { tl.x + ring_r * 3 + rings_unit, tl.y + ring_r },
        ring_r - static_cast<int>(rings_unit * 0.5)};

    c_black.set_color(Color::black);
    c_black.set_style(Line_style(Line_style::solid, rings_unit));

    Circle c_red {
        { tl.x + ring_r * 5 + rings_unit * 2, tl.y + ring_r },
        ring_r - static_cast<int>(rings_unit * 0.5)};

    c_red.set_color(Color::red);
    c_red.set_style(Line_style(Line_style::solid, rings_unit));

    Circle c_yellow {
        { tl.x + ring_d + static_cast<int>(rings_unit * 0.5),
         tl.y + ring_d - static_cast<int>(rings_unit * 0.5) },
        ring_r - static_cast<int>(rings_unit * 0.5)};

    c_yellow.set_color(Color::yellow);
    c_yellow.set_style(Line_style(Line_style::solid, rings_unit));

    Circle c_green {
                   { tl.x + ring_d * 2 + static_cast<int>(rings_unit * 1.5),
         tl.y + ring_d - static_cast<int>(rings_unit * 0.5) },
        ring_r - static_cast<int>(rings_unit * 0.5)};

    c_green.set_color(Color::green);
    c_green.set_style(Line_style(Line_style::solid, rings_unit));

    win.attach(c_blue);
    win.attach(c_black);
    win.attach(c_red);
    win.attach(c_yellow);
    win.attach(c_green);

    win.wait_for_button();

}
