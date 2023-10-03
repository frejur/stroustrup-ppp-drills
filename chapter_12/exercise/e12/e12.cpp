#define _USE_MATH_DEFINES
#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include <vector>
#include <math.h>
#include <random>
#include <memory>

/* Write a program that draws "starlike" patterns by
 * connecting points on a superellipse */

double sgn(double num)
{
    return (
        (num != 0) *
        (num > 0 ? 1 : -1));
}

vector<int> getSuperXY (
    double a, double b,
    double m, double n,
    double step, double radius)
{
    double t;
    vector<int> xy {0, 0};
    m = { max(0.01, m) };
    n = { max(0.01, n) };
    step = { min(max(0, step), 1.0) };

    t = { M_PI * 2.0 * step };

    xy[0] = {
        (int)static_cast<int>(
            pow(abs(cos(t)), 2/m) *
            a * sgn(cos(t)) * radius) };
    xy[1] = {
        (int)static_cast<int>(
            pow(abs(sin(t)), 2/n) *
            b * sgn(sin(t)) * radius) };
    return xy;
}

double randNum() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1,100);
    return dist(mt) * 0.01;
}

unique_ptr<Closed_polyline> plotSuper(
    int x,	int y,
    double a, double b, double m, double n,
    int N, int radius)
{
    unique_ptr<Closed_polyline> e( new Closed_polyline );
    e->set_color(Color::black);
    e->set_style(
        Line_style(Line_style::Line_style_type::solid, 1));

    for (int i = 0; i < N; ++i) {
        vector<int> xy {
            getSuperXY(a, b, m, n, 1.0/N * i, radius)
        };
        xy[0] += x; xy[1] += y;
        e->add({ xy[0], xy[1] });
    }
    return e;
}

int main()
{
    const int ww { 640 };
    const int wh { 640 };
    Simple_window win {
        {10, 10}, ww, wh, "Superb Ellipses" };

    const int mid_x { static_cast<int>(ww / 2) };
    const int mid_y { static_cast<int>(wh / 2) };

    const int N { 1000 }; // Number of points

    const double radius { 150 };
    const int radius_i { static_cast<int>(radius) };

    Graph_lib::Rectangle canvas {
        {mid_x - radius_i, mid_y - radius_i},
        radius_i * 2, radius_i * 2
    };
    canvas.set_fill_color(fl_color_cube(4,7,3));
    canvas.set_color(fl_color_cube(4,7,3));
    canvas.set_style(
        Line_style(Line_style::Line_style_type::solid,
        static_cast<int>(round(radius * 0.075))));
    win.attach(canvas);

    vector<unique_ptr<Closed_polyline>> eli_v;

    double n {2};
    double m {2};
    double rand_m, rand_n;
    for(int i=0; i < 8; ++i) {
        if (i>0) {
            rand_m = round((randNum()) * 200) / 100;
            rand_n = round((randNum()) * 200) / 100;
            m = min(rand_m, m);
            n = min(rand_n, n);
        }
        eli_v.push_back(
            plotSuper(
                mid_x, mid_y,
                1, 1,
                m, n,
                N, radius)
        );
        win.attach(*eli_v.back());
    }

    win.wait_for_button();

}
