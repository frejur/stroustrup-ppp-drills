#include "../lib/Simple_window.h"
#include "../lib/Graph.h"
#include <system_error>
#include <iostream>

int main()
{
    try
    {
        Graph_lib::Point tl{ 100, 100 };

        Simple_window win{ tl, 600, 400, "My Window" };

        // Axes
        Graph_lib::Axis xa{
            Graph_lib::Axis::x,
            Graph_lib::Point{ 20, 300 },
            280,
            10,
            "x axis"
        };
        win.attach(xa);

        Graph_lib::Axis ya{
            Graph_lib::Axis::y,
            Graph_lib::Point{ 20, 300 },
            280,
            10,
            "y axis"
        };
        ya.set_color(Graph_lib::Color::cyan);
        ya.label.set_color(Graph_lib::Color::dark_red);
        win.attach(ya);

        win.set_label("Axes");
        win.wait_for_button();

        // Graphed function
        Function sine {
            sin,
            0,
            100,
            Graph_lib::Point{ 20, 150},
            1000,
            50,50
        };

        win.attach(sine);
        sine.set_color(Color::green);

        win.set_label("Graphed function");
        win.wait_for_button();

        // Polygon
        Graph_lib::Polygon poly;
        poly.add(Graph_lib::Point{ 300, 200 });
        poly.add(Graph_lib::Point{ 350, 100 });
        poly.add(Graph_lib::Point{ 400, 200 });

        poly.set_color(Color::red);
        poly.set_style(Line_style::dash);
        win.attach(poly);

        win.set_label("Polygon");
        win.wait_for_button();

        // Rectangle
        Graph_lib::Rectangle rect { Point {200, 200 }, 100, 50 };
        win.attach(rect);

        win.set_label("Rectangle");
        win.wait_for_button();

        // Polylines
        Graph_lib::Closed_polyline poly_rect;
        poly_rect.add(Graph_lib::Point{ 100, 50 });
        poly_rect.add(Graph_lib::Point{ 200, 50 });
        poly_rect.add(Graph_lib::Point{ 200, 100 });
        poly_rect.add(Graph_lib::Point{ 100, 100 });
        poly_rect.add(Graph_lib::Point{ 50, 75 });
        win.attach(poly_rect);

        win.set_label("Polyline (Faux rectangle)");
        win.wait_for_button();

        // Fill colors / borders
        rect.set_fill_color(Graph_lib::Color::yellow);
        poly.set_style(Line_style(Line_style::dashdot, 4));
        poly_rect.set_style(Line_style(Line_style::dash, 2));
        poly_rect.set_fill_color(Graph_lib::Color::green);

        win.set_label("Fill colors / borders");
        win.wait_for_button();

        // Text
        Graph_lib::Text t{ Graph_lib::Point{ 150, 150 }, "Hello, world" };
        win.attach(t);

        win.set_label("Text");
        win.wait_for_button();

        // Text formatting
        t.set_font(Graph_lib::Font::times_bold);
        t.set_font_size(20);

        win.set_label("Text formatting");
        win.wait_for_button();

        // Image
        Graph_lib::Image img{ Graph_lib::Point{ 100, 50 }, "img_drill/pelikan.jpg"};
        win.attach(img);

        win.set_label("Image");
        win.wait_for_button();

        // Move Image
        img.move(100, 200);

        win.set_label("Move Image");
        win.wait_for_button();

        // And much more
        Graph_lib::Circle c{
            Graph_lib::Point{ 100, 200 },
            50
        };
        Graph_lib::Ellipse e{
            Graph_lib::Point{ 100, 200 },
            75,
            25
        };
        Graph_lib::Mark m{ Point{ 100, 200 }, 'x' };

        e.set_color(Graph_lib::Color::dark_red);

        ostringstream oss;
        oss << "screen size: " << x_max() << 'x' << y_max()
            << "; windows size: "
                << win.x_max() << 'x' << win.y_max();
        Graph_lib::Text sizes{ Point{ 100, 20 }, oss.str() };

        Graph_lib::Image pigeon{ Point{ 225, 225 }, "img_drill/pigeon.jpg" };
        pigeon.set_mask(Point{ 40, 40 }, 200, 250);

        win.attach(c);
        win.attach(e);
        win.attach(m);
        win.attach(sizes);
        win.attach(pigeon);
        win.set_label("And much more");

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
