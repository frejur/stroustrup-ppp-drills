#include "../ch15_helpers.h"
#include "bar_chart.h"

chart::Bar::Bar(const Bar_chart& parent_chart,
                const string& label,
                long double x_value,
                long double y_value)
    : Chart_element::Chart_element(parent_chart, label, x_value, y_value)
{}

void chart::Bar::draw_lines() const
{
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

Graph_lib::Point chart::Bar::label_offset() const
{
	int offs_x = -1
	             * static_cast<int>(std::round(
	                 static_cast<const Bar_chart&>(par).bar_width() * 0.5));
	int offs_y = par.origin().y - par.position_from_value(0, y_value()).y;
	return {offs_x, offs_y};
}
