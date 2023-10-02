#ifndef PENTAGONFROMSQUARE_H
#define PENTAGONFROMSQUARE_H
#include "TrigHelpers.h"

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
 *
 * There are mutliple ways to proceed from this point on but
 * the code in this example uses the triangles formed on
 * either side of the smaller square to calculate the
 * position and radius of the pentagon.
 *
 * Angles:         ,
 * ~~~~~~~       ....
 * a = 54      ..    ..
 * b = 18    ..        ..
 * c = 108 ..            ..
 *       ..┌──────────────┐..
 *     .. a│      s       │  ..
 *  A ,c   │              │    . B
 *    \    │              │    /
 *     \   │s            s│   /
 *      \  │              │  /
 *       \b│              │ /
 *        \│      s       │/
 *         └──────────────┘
 *          \            /
 *           '──────────'
 */

class PentagonFromSquare
{
private:
    int offset_x, offset_y;
    int side;
    int radius;
public:
    PentagonFromSquare(int sqr_side) :
        offset_x (0), offset_y (0),
        side (0), radius(0)
    {
        offset_x = {
            (int)round(
                (
                    sqr_side *
                    sin(TRI::deg_to_rad(18)) *
                    sin(TRI::deg_to_rad(54))
                ) /
                sin(TRI::deg_to_rad(108))
            )
        };
        offset_y = {
            (int)round(
                offset_x / tan(TRI::deg_to_rad(54))
            )
        };
        int top_w {
            (int)round(
                sqr_side + offset_x * 2
            )
        };
        side = {
            (int)round(
                (top_w * 0.5) / sin(TRI::deg_to_rad(54))
            )
        };
        radius = {
            (int)round(
                (side * 0.5) / cos(TRI::deg_to_rad(54))
            )
        };
    }

    int getOffset_x() const { return offset_x; }
    int getOffset_y() const { return offset_y; }
    int getRadius() const { return radius; }
    int getSide() const { return side; }
};

#endif // PENTAGONFROMSQUARE_H
