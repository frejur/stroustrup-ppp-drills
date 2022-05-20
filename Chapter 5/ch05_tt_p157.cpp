#include "std_lib_facilities.h"

namespace ch05_tt_p157
{
    /*  So we work over our program again and get 10.3923.
        (...)
        Our hexagon was regular with 2cm sides. Did we get that
        answer right? Just do the “back of the envelope”
        calculation. Take a piece a paper and scribble on it.
        Don’t feel that’s beneath you. Many famous scientists
        have been greatly admired for their ability to come up
        with an approximate answer using a pencil and the back
        of an envelope (or a napkin). This is an ability —
        a simple habit, really — that can save us a lot of
        time and confusion.
        */

    float hexagon_area(float side)
    {
        // Calculates area of a likesided hexagon
        return (3 * sqrt(3) / 2.0) * pow(side, 2);
    }

    int main()
    {
        constexpr float given_side{ 2 };
        constexpr float given_answer{ 10.3923 };

        cout << "A hexagon where each side is "
             << given_side << ".\n";
        cout << "The expected area is: "
             << given_answer << '\n';

        float area = hexagon_area(given_side);

        cout << "The calculated area is: " << area << '\n';

        return 0;
    }
}