#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"

/* Exercise 7: Draw a two-dimensional house. */

int main()
{
    const int ww { 640 };
    const int wh { 320 };
    Simple_window win { {10, 10}, ww, wh, "A house" };

    const int mid_x { static_cast<int>(ww / 2) };
    const int mid_y { static_cast<int>(wh / 2) };

    const int house_w { 450 };
    const int house_h { 300 };

    const int roof_h { static_cast<int>(house_h * 0.2) };
    const int walls_h { house_h - roof_h };

    Point roof_top { mid_x, mid_y - static_cast<int>(house_h / 2) };
    Point roof_left {
        roof_top.x - static_cast<int>(house_w / 2),
        roof_top.y + roof_h};
    Point roof_right { roof_left.x + house_w, roof_left.y };

    const int chim_w { static_cast<int>(house_w * 0.125) };
    Point chim_top_left {
        static_cast<int>(roof_left.x + house_w * 0.25 - chim_w * 0.5),
        roof_top.y};

    Graph_lib::Rectangle chim { chim_top_left, chim_w, roof_h };
    chim.set_fill_color(Color::black);
    chim.set_color(Color::invisible);
    win.attach(chim);

    Closed_polyline roof;
    roof.add(roof_top);
    roof.add(roof_right);
    roof.add(roof_left);
    roof.set_fill_color(Color::dark_red);
    roof.set_color(Color::invisible);
    win.attach(roof);

    Graph_lib::Rectangle walls { {roof_left}, house_w, walls_h };
    walls.set_fill_color(Color::white);
    walls.set_color(Color::invisible);
    win.attach(walls);

    const int div_by_10 { static_cast<int>(house_w / 10) };
    const int div_diff { house_w - div_by_10 * 10 };
    const int pad_w { div_by_10 };
    const int pad_big_w { div_by_10 + div_diff };
    const int door_w { div_by_10 * 2 };
    const int win_w { door_w };
    const int door_h { static_cast<int>((house_h - roof_h) * 0.7)};
    const int win_h { static_cast<int>(door_h * 0.5) };

    Point walls_bottom_left { roof_left.x, roof_top.y + house_h };

    Graph_lib::Rectangle door {
        {walls_bottom_left.x + pad_w, walls_bottom_left.y - door_h },
        door_w,
        door_h};
    door.set_color(Color::black);
    win.attach(door);

    Graph_lib::Rectangle win_01 {
        { door.point(0).x + door.width() + pad_big_w, door.point(0).y },
        win_w,
        win_h};
    win_01.set_color(Color::black);
    win.attach(win_01);

    Graph_lib::Rectangle win_02 {
        { win_01.point(0).x + win_01.width() + pad_w, door.point(0).y },
        win_w,
        win_h};
    win_02.set_color(Color::black);
    win.attach(win_02);

    win.wait_for_button();

}
