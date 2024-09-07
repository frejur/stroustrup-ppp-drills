#ifndef SHAPE_GROUP_H
#define SHAPE_GROUP_H
#include "../../../lib/Graph.h"

namespace grp_shp {

class Shape_group : public Graph_lib::Shape
{
public:
	Shape_group(Graph_lib::Point origin)
	    : o(origin){};
	// Global
	void move(int offset_x, int offset_y) override;
	void set_color(Graph_lib::Color col);
	void set_style(Graph_lib::Line_style sty);
	void set_fill_color(Graph_lib::Color col);
	// Element-wise
	virtual void move(int offset_x, int offset_y, int elem_index);
	void set_color(Graph_lib::Color col, int elem_index);
	void set_style(Graph_lib::Line_style sty, int elem_index);
	void set_fill_color(Graph_lib::Color col, int elem_index);
	// Container
	void add(Graph_lib::Shape& shape) { elem.push_back(shape); };
	void add(Graph_lib::Shape* shape) { elem.push_back(shape); };
	int number_of_elements() const { return elem.size(); };

protected:
	Graph_lib::Point o;
	Graph_lib::Vector_ref<Graph_lib::Shape> elem;
	virtual void draw_lines() const override;
	int valid_index(int idx) const;

private:
	virtual Graph_lib::Point point(int i) const override { return {0, 0}; };
};

} // namespace grp_shp

#endif // SHAPE_GROUP_H
