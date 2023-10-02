#define _USE_MATH_DEFINES
#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include "RegularPoly.h"
#include <cmath>
#include "TrigHelpers.h"
#include "SquareFromTriangle.h"
#include "PentagonFromSquare.h"
#include "HexagonFromPentagon.h"

/* Exercise 11. Draw an equilateral triangle, inscribe it
 * 				inside a square, then keep inscribing the
 * 				shape last drawn inside another regular
 * 				polygon, always increasing the number of
 * 				sides N by 1.
 *
 *              All the corner points of the inner shape
 *              should connect with the borders of its
 *              outer shape.
 *
 *              (This is only possible until N = 5,
 *               this program draws shapes up until that
 *               point, and then draws the largest possible
 *               pentagon contained within a hexagon) */

using namespace Graph_lib;


int main()
{
    const int ww { 840 };
    const int wh { 680 };
    Simple_window win{
        {0,0}, ww, wh, "Inscribe Polyons" };

    // Triangle
    const int tri_rad { 200 };
    int tri_side = {
        static_cast<int>(round(std::sqrt(3.0) * tri_rad))
    };
    RegularPolygon tri {
        { (int)round(ww * 0.5 + tri_rad * 0.75),
          (int)round(wh * 0.5 + tri_rad * 0.5) },
        tri_rad, 3,
        (float)TRI::deg_to_rad(90 + 15)
    };
    tri.set_color(Color::black);
    tri.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(tri);

    // Square
    SquareFromTriangle sqr_tri { (double)tri_side };
    RegularPolygon sqr {
        tri.point(2), sqr_tri.getRadius(), 4,
        (float)TRI::deg_to_rad(225)
    };
    sqr.set_color(Color::black);
    sqr.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(sqr);

    // Pentagon
    PentagonFromSquare pen_sqr { (int)sqr_tri.getSide() };
    RegularPolygon pen {
        { sqr.point(3).x - pen_sqr.getOffset_x() * 1,
          sqr.point(3).y + pen_sqr.getOffset_y() * 1},
        pen_sqr.getRadius(), 5,
        (float)TRI::deg_to_rad(72 * 4)
    };
    pen.set_color(Color::black);
    pen.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(pen);

    // Hexagon
    HexagonFromPentagon hex_pen { pen_sqr.getSide() };
    RegularPolygon hex {
        { pen.point(3).x + hex_pen.getOffset_x(),
          pen.point(3).y + hex_pen.getOffset_y()},
        hex_pen.getSide(), 6,
        (float)TRI::deg_to_rad(30 * 3)
    };
    hex.set_color(Color::black);
    hex.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(hex);

    win.wait_for_button();

    return 0;
}
