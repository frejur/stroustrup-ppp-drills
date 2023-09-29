#define _USE_MATH_DEFINES
#include "../../lib/Simple_window.h"
#include "../../lib/Graph.h"
#include "inscr_poly.h"
#include <cmath>

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

double sec(double ang_rad)
{
    return 1.0 / std::cos(ang_rad);
}

double cot(double ang_rad)
{
    return std::cos(ang_rad) / std::sin(ang_rad);
}

double deg_to_rad(float ang_in_deg) {
    return (
        min(360, max(0, ang_in_deg)) *
        M_PI / 180);
}

int main()
{
    const int ww { 840 };
    const int wh { 680 };
    Simple_window win{
        {0,0}, ww, wh, "Inscribe Polyons" };

    // Triangle
    const int tri_rad { 200 };
    int tri_side = static_cast<int>(round(std::sqrt(3.0) * tri_rad));
    RegularPolygon tri {
        {520, 440}, tri_rad, 3, (float)deg_to_rad(90 + 15) };
    tri.set_color(Color::black);
    tri.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(tri);

    /* Square
     * "The largest equilateral triangle which can be
     * inscribed <in a unit square> is oriented at
     * an angle of 15 degrees and has side length of:
     * s = sec(15 degrees) = sqrt(6) - sqrt(2)"
     *
     * (Source: https://mathworld.wolfram.com/EquilateralTriangle.html)
     */

    double sqr_side { tri_side / sec(deg_to_rad(15)) };
    int sqr_rad {
        (int)round(sqrt(sqr_side * sqr_side * 2) * 0.5) };
    RegularPolygon sqr {
        tri.point(2), sqr_rad, 4,
        (float)deg_to_rad(225)
    };
    sqr.set_color(Color::black);
    sqr.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(sqr);

    /* Pentagon
     *
     * 1.   ,'.          2.   ,'.
     *    ,'   `.           ,'   `.
     *  ,'       `.      A,_________.B
     *  \         /       |         |
     *   \       /        |\       /|
     *    \_____/  	      | \_____/ |
     *                    |_________|C
     *
     * 1. Draw a pentagon with its "base" parallel
     * to the X-axis.
     *
     * 2. Join the two parallel points A and B below
     * the topmost point, and use the resulting line
     * to draw a square extending past the base of the
     * polygon.
     *
     * 3.    T	      4.       T
     *      ,:.               ,:.
     *    ,' \ `.           .__\__.
     * A,_____\_.B        ,'|   \ |`.
     *  |      \  |       \ |    \| /
     *  |\      \/|        \|_____X/
     *  | \_____/\|         \_____/\
     *  |_________|C                C
     *
     * 3. Join the lower corner point C of the square
     * with the topmost point T of the pentagon.
     *
     * 4. The point of intersection X of that resulting
     * line and the bounds of the pentagon marks
     * the lower corner point of the largest square
     * inscribed in the pentagon.
     *
     * Source: https://www.graphicalcommunication.com/pdfs/drawinglargestsquareinsideapolygon.pdf
     */


    int pen_offs_x {
        (int)round(
            (sqr_side *
             sin(deg_to_rad(18) * sin(deg_to_rad(54)))) /
            sin(deg_to_rad(108))
        )};
    int pen_offs_y {
        (int)round(pen_offs_x / tan(deg_to_rad(54))) };
    int pen_top_w {
        (int)round(sqr_side + pen_offs_x * 2) };
    int pen_side {
        (int)round(
            (pen_top_w * 0.5) / sin(deg_to_rad(54))
        )};
    int pen_rad {
        (int)round(
            (pen_side * 0.5) / cos(deg_to_rad(54))) };
    RegularPolygon pen {
        { sqr.point(3).x - pen_offs_x * 1,
          sqr.point(3).y + pen_offs_y * 1},
        pen_rad, 5, (float)deg_to_rad(72 * 4)
    };
    pen.set_color(Color::black);
    pen.set_style(
        Line_style(Line_style::Line_style_type::solid, 1));
    win.attach(pen);


    win.wait_for_button();

    return 0;
}
