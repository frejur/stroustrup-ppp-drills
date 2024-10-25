#ifndef ARROW_H
#define ARROW_H

#include "../../../lib/Graph.h"

class Arrow : public Graph_lib::Shape
{
public:
	Arrow(Graph_lib::Point origin, Graph_lib::Point end);
	void show() { is_hidden = false; };
	void hide() { is_hidden = true; };
	bool is_visible() const { return !is_hidden; };
	void draw_lines() const;

	void new_start_and_end_points(Graph_lib::Point start, Graph_lib::Point end);

private:
	bool is_hidden;

	void draw_arrow(Graph_lib::Point origin, Graph_lib::Point end) const;
	void draw_arrow_head(Graph_lib::Point end, float angle) const;
};

#endif // ARROW_H
