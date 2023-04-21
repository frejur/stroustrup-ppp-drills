#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include <vector>
#include <cmath>
#include <memory>

/* Exercise 4. Draw a 3x3 tic-tac-toe board of alternating white and red squares */

int get_checker_size(int desired_dim, int num_checkers, int border_thk)
{
    int pad = (num_checkers - 1) * border_thk;
    return static_cast<int>((desired_dim - pad) / num_checkers);
}

int main()
{
    const int ww { 640 };
    const int wh { 480 };
    Simple_window win{ {100, 100}, ww, wh, "Tic-tac-toe" };

    constexpr int chk_num { 15 }; // 3x3 grid
    constexpr int brd_dim_desired { 360 };
    constexpr int border { 4 };
    const int chk_sz { get_checker_size(brd_dim_desired, chk_num, border) };
    const int brd_dim { chk_sz * chk_num + (chk_num - 1) * border };
    const int margin_l { static_cast<int>((ww - brd_dim) * 0.5) };
    const int margin_t { static_cast<int>((wh - brd_dim) * 0.5) };
    const Graph_lib::Color clr_odd { Color::white };
    const Graph_lib::Color clr_even { Color::dark_red };

    Graph_lib::Rectangle brd {
        { margin_l, margin_t },
        { margin_l + brd_dim, margin_t + brd_dim }
    };

    brd.set_fill_color(Graph_lib::Color::black);

    std::vector<std::unique_ptr<Graph_lib::Rectangle>> chk_v;
    int x, y;
    bool is_odd { true };
    bool alt_rows { (chk_num * chk_num) % 2 == 0 };
    for (int i = 0; i < chk_num * chk_num; ++i) {
        x = (i % chk_num);
        y = std::floor(i / chk_num);
        std::unique_ptr<Graph_lib::Rectangle> r (
            new Graph_lib::Rectangle(
                Graph_lib::Point {
                    margin_l +
                        x * border +
                        x * chk_sz,
                    margin_t +
                        y * border +
                        y * chk_sz
                },
                chk_sz,
                chk_sz
            )
        );
        chk_v.push_back(std::move(r));

        if (alt_rows && x == 0)
            is_odd = !is_odd;
        if (is_odd)
            chk_v[i]->set_fill_color(clr_odd);
        else
            chk_v[i]->set_fill_color(clr_even);

        is_odd = !is_odd;

        chk_v[i]->set_style(Graph_lib::Line_style(Graph_lib::Line_style::Line_style_type::solid, 0));
        chk_v[i]->set_color(Graph_lib::Color::invisible);
    }

    win.attach(brd);

    for (auto &r : chk_v) {
        win.attach(*r);
    }

    win.wait_for_button();
}
