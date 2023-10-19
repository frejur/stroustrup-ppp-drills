#ifndef ARROW_H
#define ARROW_H

#include "../../lib/Graph.h"

class Arrow : public Graph_lib::Shape
{
private:
	void draw_arrow(Graph_lib::Point origin, Graph_lib::Point end);
	void draw_line(Graph_lib::Point origin, Graph_lib::Point end);
	void draw_arrow_head(Graph_lib::Point end, float angle);
public:
	Arrow(Graph_lib::Point origin, Graph_lib::Point end);
};

#endif // ARROW_H
