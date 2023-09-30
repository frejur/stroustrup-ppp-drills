#ifndef SQUAREFROMTRIANGLE_H
#define SQUAREFROMTRIANGLE_H
#include "TrigHelpers.h"

// Square
//
// 		"The largest equilateral triangle which can be
// 		inscribed <in a unit square> is oriented at
// 		an angle of 15 degrees and has side length of:
// 		s = sec(15 degrees) = sqrt(6) - sqrt(2)"
//
// 		(Source: https://mathworld.wolfram.com/EquilateralTriangle.html)
//
// 1           : 2                  : 3
//                                         ┌─────────┬───
//      +      :          +         :      │   ,+.   │ 15°
//     / \              */ \*              └─►*/ \*.◄┘
//  s //^\\ s  :      * //^\\ *     :      ,* /   \ *.
//   //   \\        *  //   \\  *        ,*  /     \  *.
//  //  s  \\  :  +   //  s  \\   + :   +.  /       \  ,+
// <=========>      *.-=======-.*         *:---------;*
//             :     │*       *│    :       *. 45° ,*
//                   │  *   *  │              *. ,*
//             :   s │    +    │ s  :           +
//                   │  *   *  │
//             :     │*       *│    :
//                   '─────────'
//             :          s         :

class SquareFromTriangle
{
private:
    double side;
    int radius;
public:
    SquareFromTriangle(double tri_side) :
        side (0), radius (0)
    {
        side = { tri_side / TRI::sec(TRI::deg_to_rad(15)) };
        radius = {
            (int)round(
                sqrt(side * side * 2) * 0.5
            )
        };
    };
    double getSide() const { return side; }
    int getRadius() const { return radius; }
};

#endif // SQUAREFROMTRIANGLE_H
