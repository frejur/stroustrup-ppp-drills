#ifndef ATTIRE_H
#define ATTIRE_H
#include "../../lib/Graph.h"

namespace emot {

class Attire : Graph_lib::Shape
{
protected:
	virtual void draw_lines() const = 0;
};

class Hat : Attire
{};

} // namespace emot
#endif // ATTIRE_H
