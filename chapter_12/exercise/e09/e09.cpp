#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include <system_error>
#include <iostream>

int main()
{
    try
    {
        const string txt { "A friend" };
        Point tl{ 100, 100 };
        Simple_window win{ tl, 600, 400, txt };

        // Image
        Image img{ Point{ 100, 50 }, "img_e09/a_friend.gif"};
        win.attach(img);

        // Label
        Text label { { 100, 365 }, txt };
        label.set_font(Graph_lib::Font::screen_bold);
        label.set_font_size(18);
        label.set_color(Color::black);
        win.attach(label);

        win.wait_for_button();
        return 0;
    }
    catch (exception& e) {
        return 1;
    }
    catch (...) {
        return 2;
    }
}
