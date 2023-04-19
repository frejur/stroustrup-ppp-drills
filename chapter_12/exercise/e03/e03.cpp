#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include "initials.h"

/* Exercise 3. Draw your initials 150 pixels high, using a thick line and different colors
   for each character. */

int main()
{
    const int ww { 640 };
    const int wh { 480 };
    Simple_window win{ {100, 100}, ww, wh, "Initials" };

    const int h { 150 };
    const int w { static_cast<int>(h / 2) };
    const int pad { static_cast<int>(w * 0.25) };
    const int margin_l { static_cast<int>((ww - (w * 2 + pad)) * 0.5) };
    const int margin_t { static_cast<int>((wh - h) * 0.5) };
    const Graph_lib::Color clr_f { Color::dark_green };
    const Graph_lib::Color clr_j { Color::green };

    InitialByShape i_f { 'F', { margin_l, margin_t }, h };
    InitialByShape i_j { 'j', { margin_l + w + pad, margin_t }, h };

    i_f.set_color(clr_f);
    i_f.set_style(Line_style(Line_style::solid, 5));

    i_j.set_color(clr_j);
    i_j.set_style(Line_style(Line_style::solid, 5));

    win.attach(i_f);
    win.attach(i_j);
    win.wait_for_button();
}
