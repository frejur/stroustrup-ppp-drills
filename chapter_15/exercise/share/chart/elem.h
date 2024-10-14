#ifndef GRAPH_ELEMENT_H
#define GRAPH_ELEMENT_H
#include "../../../lib/Graph.h"

namespace chart {

class Chart;

class Chart_element : public Graph_lib::Shape
{
public:
	void draw_lines() const override = 0;
	long double x_value() const { return x_val; };
	long double y_value() const { return y_val; };
	std::string label() const { return lb; };
	void set_x_value(double x) { x_val = x; };
	void set_y_value(double y) { y_val = y; };
	void set_label(const std::string& l) { lb = l; };

protected:
	Chart_element(const Chart& parent_chart,
	              const std::string& label,
	              double x_value,
	              double y_value);
	const Chart& par;
	virtual void draw_label() const;
	virtual Graph_lib::Point label_offset() const { return {0, 0}; };

private:
	long double x_val;
	long double y_val;
	std::string lb;
};
} // namespace chart

#endif // GRAPH_ELEMENT_H
