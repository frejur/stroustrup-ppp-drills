#include "bar_chart.h"
#include "../ch15_helpers.h"
#include <algorithm>

namespace {
constexpr int bar_min_width{2};
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

chart::Bar_chart::Bar_chart(Graph_lib::Point top_left,
                            int width,
                            int height,
                            int bars_padding)
    : Chart::Chart(top_left, width, height)
    , auto_pad_bars(bars_padding == 0)
    , color({default_color()})
    , fill({default_fill_color()})
{
	upd_colors();
	pad_graph_btm = lb_fnt_sz + pad_v;
	cv.hide_x_axis_notches();
	cv.hide_x_values();
}

//------------------------------------------------------------------------------

void chart::Bar_chart::add(const string& label, long double value)
{
	long double x = elem.size() + 1;
	elem.push_back(new Bar(*this, label, x, value));

	refresh();
}

void chart::Bar_chart::set_colors(std::initializer_list<Graph_lib::Color> cv)
{
	color.clear();
	for (Graph_lib::Color c : cv) {
		color.push_back(c);
	}
	upd_colors();
}

void chart::Bar_chart::set_fill_colors(std::initializer_list<Graph_lib::Color> cv)
{
	fill.clear();
	for (Graph_lib::Color c : cv) {
		fill.push_back(c);
	}
	upd_colors();
}

Graph_lib::Color chart::Bar_chart::color_by_index(int n) const
{
	if (color.empty()) {
		return default_color();
	}
	return color[n % color.size()];
}

Graph_lib::Color chart::Bar_chart::fill_color_by_index(int n) const
{
	if (fill.empty()) {
		return default_fill_color();
	}
	return fill[n % fill.size()];
}

//------------------------------------------------------------------------------

void chart::Bar_chart::set_bars_padding(int p)
{
	auto_pad_bars = false;
	if (p <= 0) {
		throw std::runtime_error("Padding must be a value above 0");
	}
	pad_bars = p;

	upd_layout();
}
void chart::Bar_chart::unset_bars_padding()
{
	auto_pad_bars = true;
	upd_layout();
}

//------------------------------------------------------------------------------

void chart::Bar_chart::sort_by_label(Order o)
{
	std::vector<int> oid_v;
	for (int i = 0; i < elem.size(); ++i) {
		Bar& b{static_cast<Bar&>(elem[i])};
		oid_v.push_back(b.x_value());
	}

	if (o == Order::Asc) {
		std::sort(oid_v.begin(), oid_v.end(), [this](int oid_a, int oid_b) {
			return elem[oid_a].label() < elem[oid_b].label();
		});
	} else {
		std::sort(oid_v.begin(), oid_v.end(), [this](int oid_a, int oid_b) {
			return elem[oid_a].label() > elem[oid_b].label();
		});
	}

	for (int j = 0; j < elem.size(); ++j) {
		Bar& b{static_cast<Bar&>(elem[j])};
		b.set_x_value(j);
	}
	upd_colors();
}

//------------------------------------------------------------------------------

ch15_hlp::Text_alignment chart::Bar_chart::label_alignment() const
{
	return ch15_hlp::Text_alignment::Bottom;
}

//------------------------------------------------------------------------------

void chart::Bar_chart::upd_post_layout()
{
	if (elem.size() == 0) {
		pad_bars = 0;
		return;
	}
	int pad = 0;
	if (auto_pad_bars) {
		pad = static_cast<int>(std::round(cv.width() / number_of_bars() * 0.1));
	} else {
		int combined_min_bar_w{bar_min_width * number_of_bars()};
		int available_space{cv.width()
		                    - (cv.origin().x - canvas_top_left_corner().x)};
		int space_remaining{available_space - combined_min_bar_w};
		int max_pad = static_cast<int>(
		    std::round(space_remaining / number_of_bars()));
		pad = (std::min)(max_pad, pad_bars);
	}
	pad_bars = pad;
}

void chart::Bar_chart::upd_colors()
{
	for (int i = 0; i < elem.size(); ++i) {
		Bar& b{static_cast<Bar&>(elem[i])};
		b.set_color(color_by_index(b.x_value() - 1));
		b.set_fill_color(fill_color_by_index(b.x_value() - 1));
	}
}
