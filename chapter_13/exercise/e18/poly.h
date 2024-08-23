#ifndef POLY_H
#define POLY_H

#include "../../lib/Graph.h"

namespace Graph_lib {

struct Poly : Polygon
{
	// Useful when the list of points is not known at compile time.
	// The vector can be modified before passing it to the constructor.
	Poly(std::vector<Point> pts)
	    : Polygon()
	{
		for (auto& pt : pts) {
			add(pt);
		}
	}

	// Already implemented in 'Polygon'. (The 'Graph.h' and 'Graph.cpp'
	//                                    files are different from the
	//                                    ones used in the book)
	// Useful when you want to create a polygon using a list of points
	// known at compile time.
	Poly(std::initializer_list<Point> lst)
	    : Polygon(lst){};
};

} // namespace Graph_lib

#endif // POLY_H
