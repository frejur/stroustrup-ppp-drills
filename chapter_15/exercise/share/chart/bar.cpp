#include "bar_chart.h"
namespace {
const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black,
	                                Graph_lib::Color::Transparency::invisible};
	return c;
}

const Graph_lib::Color& default_fill_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::dark_blue};
	return c;
}
} // namespace

chart::Bar::Bar(const Bar_chart& parent_chart,
                const string& label,
                long double x_value,
                long double y_value)
    : Chart_element::Chart_element(parent_chart, label, x_value, y_value)
{}

Graph_lib::Color chart::Bar::bar_color(int bar_idx) const
{
	if (bar_idx < number_of_bars()) {
		return col_v.at(bar_idx);
	}
	return default_color();
}

Graph_lib::Color chart::Bar::bar_fill_color(int bar_idx) const
{
	if (bar_idx < number_of_bars()) {
		return fill_v.at(bar_idx);
	}
	return default_fill_color();
}

void chart::Bar::set_bar_color(Graph_lib::Color col, int bar_idx)
{
	init_colors();
	col_v.at(bar_idx) = col;
}

void chart::Bar::set_bar_fill_color(Graph_lib::Color col, int bar_idx)
{
	init_colors();
	fill_v.at(bar_idx) = col;
}
void chart::Bar::init_colors()
{
	if (col_v.empty()) {
		col_v = std::vector<Graph_lib::Color>(number_of_bars(), default_color());
	}
	if (fill_v.empty()) {
		fill_v = std::vector<Graph_lib::Color>(number_of_bars(),
		                                       default_fill_color());
	}
};

Graph_lib::Point chart::Bar::label_offset() const
{
	int offs_x = -1
	             * static_cast<int>(std::round(
	                 static_cast<const Bar_chart&>(par).bar_width() * 0.5));
	int offs_y = par.origin().y - par.position_from_value(0, y_value()).y;
	return {offs_x, offs_y};
}

//------------------------------------------------------------------------------

chart::Bar_single::Bar_single(const Bar_chart& parent_chart,
                              const string& label,
                              long double x_value,
                              long double y_value)
    : Bar::Bar(parent_chart, label, x_value, y_value)
{}

void chart::Bar_single::draw_lines() const
{
	Graph_lib::Color c = color();
	Graph_lib::Color cf = fill_color();

	if (y_value() == 0
	    || (!fill_color().visibility() && !color().visibility())) {
		return;
	}

	Graph_lib::Point tr{par.position_from_value(x_value(), y_value())};
	int h{std::abs(par.origin().y - tr.y)};
	const Bar_chart& bc{static_cast<const Bar_chart&>(par)};
	int tl_x{static_cast<int>(std::round(tr.x - bc.bar_width()))};
	int tl_y{tr.y};

	if (fill_color().visibility()) { // fill
		fl_color(fill_color().as_int());
		fl_rectf(tl_x, tl_y, bc.bar_width(), h);
	}

	if (color().visibility()) { // lines on top of fill
		fl_color(color().as_int());
		fl_rect(tl_x, tl_y, bc.bar_width(), h);
	}

	draw_label();
}
