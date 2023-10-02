#ifndef HEXAGONFROMPENTAGON_H
#define HEXAGONFROMPENTAGON_H
#include "TrigHelpers.h"

// Hexagon
//
// "The largest pentagon that can be fitted inside a
// regular hexagon.
//
// Proof: At least 2 vertices must be touch the hexagon,
// or else you could grow the pentagon until two did.
// If those two were not adjacent (...), you could grow the
// pentagon until the two vertices were on opposite vertices
//  of the hexagon (across its diameter). But this is
// impossible as the resulting pentagon is not inside the
// hexagon - therefore 2 adjacent vertices of the pentagon
// must touch the hexagon.
//
// The two alternatives now are for these adjacent vertices
// of the pentagon to lie on two adjacent sides of the
// hexagon (...) or on two alternate sides(...).
//
// The lower two vertices of the pentagon are on adjacent
// sides of the hexagon. We have placed the pentagon
// symmetrically to start with, and grown it so 2 further
// vertices touch the hexagon. However the top vertex
// does not touch.
//
// We can therefore make the pentagon a tiny bit bigger by
// raising it slightly (...) and then tilting(...) in fact
// we can carry on doing this until the top vertex touches
// the hexagon side.
//
// Therefore the biggest pentagon has 2 adjacent vertices
// on alternate sides of the the hexagon."
//
//             ______+_____
//            /    ,:^:.   \           1 and 2:
//           /   ,:'   ':.  \          ~~~~~~~~~~~~~~~~
//          /  ,,        ':. \         The two adjacent
//         / ,,'           '..\        vertices that touch
//        /,,'               '.\       the hexagon.
//   (1) +''                   '+ (2)
//      /::                     :\
//     / :.                    .: \      Distances on the
//     \ ::                   .:  /         X-axis:
//      \:':                  :' /       ~~~~~~~~~~~~~~~~
//       : '.                :' /       a:   From left-most
//    ◄─►:\ ::               : /            point on hexagon
//     a : \':       x      .'/           to vertex 1.
//       :  \'◄────────────►'/       x: Side of pentagon.
//       :   +--------------+      y:  Side of hexagon.
//       :....\____________/
//             ◄──────────►
//                   y
//
// X-axis:
// (x - y) / 2 + x * cos(72) + a
// =
// y / 2
//
// Y-axis:
// sqrt(3) * (x - 1) / 2 + x * sin(72)
// =
// (sqrt(3) * y) / 2 + sqrt(3) * a
//
// Value of a:
// a = y / 2 - (x - y) - x * cos(72)
//   = (sqrt(3) * (x - y) / 2 + x * sin(72) - (sqrt(3) * y) / 2)
//     /
//     sqrt(3)
//   = (x - y) / 2 - y / 2 + (x * sin(72)) / sqrt(3)
//   = x / 2 - y + (x * sin(72)) / sqrt(3)
//
// Also a:
// a = y / 2 - (x - y) - x * cos(72)
//   = y - x / 2 - x * cos(72)
//
// Which gives:
// => x / 2 - y + (x * sin(72)) / sqrt(3)
//    =
//    y - x / 2 - x * cos(72)
//
// Add y and x/2 to both sides:
// x + (x * sin(72)) / sqrt(3)
// =
// 2 * y - x * cos(72)
//
// (There's more at the website cited below, but at this
// point we can just solve for y)
//
// Source: https://www.drking.org.uk/hexagons/misc/deriv5.html
//
// Solving for y:
// 2 * y = x + (x * sin(72)) / sqrt(3) + x * cos(72)
//     y = (x + (x * sin(72) / sqrt(3) + (x * cos(72))
//         / 2
//
// The offset of the hexagon on the Y-axis:
// o = sqrt(3) * a
//   = sqrt(3) * y - x / 2 - x * cos(72)

class HexagonFromPentagon
{
private:
    int side;
    int offset_x, offset_y;
public:
    HexagonFromPentagon(int pen_side) :
        side (0),
        offset_x (0), offset_y (0)
    {
        double const& sqrt_3 { sqrt(3.0) };
        double const& cos_72 { cos(TRI::deg_to_rad(72)) };
        double const& sin_72 { sin(TRI::deg_to_rad(72)) };
        side = {
            (int)round(
                0.5 *
                (
                    pen_side * 1.0 +
                    pen_side * sin_72 /
                       sqrt_3 +
                    pen_side * cos_72
                )
            )
        };
        offset_y = {
            (int)round(
                sqrt(3.0) *
                (side -
                pen_side * 0.5 -
                pen_side * cos_72)
            )
        };
        offset_x = {
            (int)round(
                offset_y / sqrt_3
            )
        };
    };

    int getOffset_x() const { return offset_x; }
    int getOffset_y() const { return offset_y; }
    int getRadius() const { return side; }
    int getSide() const { return side; }
};
#endif // HEXAGONFROMPENTAGON_H
