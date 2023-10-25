#ifndef HEXAGONTILER_H
#define HEXAGONTILER_H
#include "../../lib/Graph.h"
#include "regularhexagon.h"
#include <memory>
#include <vector>
class HexagonTiler
{
public:
	HexagonTiler(Graph_lib::Point center, int num_tiles);
	Graph_lib::Point center() const { return c };
private:
	Graph_lib::Point c;
	void add_tile(Graph_lib::Point o);
	void add_tile(Graph_lib::Point o, int connecting_side);
	std::vector<std::unique_ptr<RegularHexagon>> tiles;
};

#endif // HEXAGONTILER_H
