#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"

/* Exercise 2. Draw a 100 x 30 Rectangle and place the text "Howdy!" inside it */

int main()
{
    Simple_window win{ {100, 100}, 640, 480, "Rectangle with text" };

    const Graph_lib::Point top_left { 25, 25 };
    const vector<int> dim { 100, 30 };
    const std::string msg { "Howdy!"};
    const int font_sz { 20 };

    Graph_lib::Rectangle rect { top_left, { top_left.x + dim[0], top_left.y + dim[1] } };

    Graph_lib::Text txt {
        { top_left.y + 10, top_left.y + dim[1] - static_cast<int>((dim[1] - font_sz) * 0.5) },
        msg
    };

    txt.set_font(Graph_lib::Font::helvetica_bold);
    txt.set_font_size(font_sz);

    win.attach(rect);
    win.attach(txt);
    win.wait_for_button();
}
