#ifndef TRIGHELPERS_H
#define TRIGHELPERS_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

namespace TRI {

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
        std::fmin((float)360,
            std::fmax((float)0, ang_in_deg)) *
        M_PI / 180);
}

} // TRI NAMESPACE
#endif // TRIGHELPERS_H
