#ifndef REGULARHEXAGON_H
#define REGULARHEXAGON_H
#include "regularpoly.h"
#include <vector>

class RegularHexagon : public RegularPolygon
{
public:
	RegularHexagon(Graph_lib::Point xy, int radius);
	void close_side(int n);
	bool side_is_open(int n) const;
private:
	static constexpr int num_sides{ 6 };
	std::vector<bool> side_states;
};

#endif // REGULARHEXAGON_H
