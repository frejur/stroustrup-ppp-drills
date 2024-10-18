#include "line_chart.h"

namespace {

const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::dark_green};
	return c;
}

} // namespace

//------------------------------------------------------------------------------

chart::Line_chart::Line_chart(Graph_lib::Point top_left_corner,
                              int width,
                              int height)
    : Chart::Chart(top_left_corner, width, height)
{
	hide_labels();
}

void chart::Line_chart::add(const string& label,
                            double start_x_value,
                            double x_unit_size,
                            std::vector<double> y_values,
                            Graph_lib::Color color = default_color())
{
	elem.push_back(
	    new Series(*this, label, start_x_value, x_unit_size, y_values));
	static_cast<Series&>(elem[elem.size() - 1]).set_color(color);

	refresh();
}

int chart::Line_chart::valid_idx(int idx) const
{
	if (elem.size() == 0) {
		throw std::runtime_error(
		    "Cannot fetch line attributes, no lines have been added");
	}
	if (idx < 0 || idx > elem.size() - 1) {
		throw std::runtime_error("Invalid index");
	}
	return idx;
}
