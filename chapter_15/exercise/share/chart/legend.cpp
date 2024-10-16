#include "legend.h"
#include "../ch15_helpers.h"
namespace {
constexpr int min_font_size{6};
constexpr int max_font_size{32};
constexpr int min_padding{1};
constexpr int max_padding{32};
constexpr int default_horizontal_padding{6};
constexpr int default_vertical_padding{6};

const Graph_lib::Font& default_font()
{
	static const Graph_lib::Font& f{Graph_lib::Font::helvetica};
	return f;
}

const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color& c{Graph_lib::Color::black};
	return c;
}

const Graph_lib::Color& default_fill_color()
{
	static const Graph_lib::Color& c{FL_GRAY};
	return c;
}
} // namespace

chart::Legend_box::Legend_box(Graph_lib::Point top_left,
                              int font_size,
                              Legend_flow element_flow)
    : fnt_sz(valid_fnt_sz(font_size))
    , pad_h(valid_pad(default_horizontal_padding))
    , pad_v(valid_pad(default_vertical_padding))
    , swatch_h(fnt_sz)
    , swatch_w(static_cast<int>(std::round(fnt_sz * 1.4)))
    , shp_sz(fnt_sz)
    , flow(element_flow)
    , fnt(default_font())
{
	add(top_left);
	set_color(default_color());
	set_fill_color(default_fill_color());
}
//------------------------------------------------------------------------------

void chart::Legend_box::draw_lines() const
{
	draw_frame();

	Graph_lib::Point tl{top_left_corner()};
	tl.x += pad_h;
	tl.y += pad_v;
	Graph_lib::Point xy{tl};
	int fnt_half_sz{static_cast<int>(std::round(fnt_sz * 0.5))};
	for (const Legend& l : leg) {
		// Draw swatch / shape
		if (l.legend_type == Legend_type::Color) {
			draw_swatch({xy.x, xy.y}, l.color, swatch_w, swatch_h);
			xy.x += swatch_w;
		} else {
			draw_plot_point({xy.x + fnt_half_sz, xy.y + fnt_half_sz},
			                l.shape_type,
			                shp_sz);
			xy.x += shp_sz;
		}
		xy.x += pad_h;

		// Draw label
		int label_w = ch15_hlp::calc_lb_w(l.label, fnt, fnt_sz);
		ch15_hlp::draw_text({xy.x, xy.y + fnt_half_sz},
		                    l.label,
		                    fnt,
		                    fnt_sz,
		                    color(),
		                    ch15_hlp::Text_alignment::Right);

		if (flow == Legend_flow::Horizontal) {
			xy.x += label_w + pad_h * 2;
		} else {
			xy.x = tl.x;
			xy.y += fnt_sz + pad_v;
		}
	}
}

//------------------------------------------------------------------------------

int chart::Legend_box::calc_w() const
{
	if (leg.size() == 0) {
		return 0;
	}

	int total_w = 0;
	int num_shapes = num_shp();
	int num_colors = leg.size() - num_shapes;
	if (flow == Legend_flow::Horizontal) {
		const std::string combined_labels{comb_lb()};
		int shape_comb_w{num_shapes * shp_sz};
		int swatch_comb_w{swatch_w * num_colors};
		int lb_w = ch15_hlp::calc_lb_w(combined_labels, fnt, fnt_sz);
		int pad_w = pad_h * leg.size();
		pad_w += (leg.size() > 1) ? (leg.size() - 1) * pad_h * 2 : 0;
		total_w = shape_comb_w + swatch_comb_w + lb_w + pad_w;
	} else {
		if (swatch_w > shp_sz) {
			total_w = (num_colors > 1) ? swatch_w : shp_sz;
		} else {
			total_w = (num_shapes > 1) ? shp_sz : swatch_w;
		}
		total_w += max_lb_w() + pad_h;
	}
	return total_w + pad_h * 2;
}

int chart::Legend_box::calc_h() const
{
	if (leg.size() == 0) {
		return 0;
	}

	int total_h = 0;
	if (flow == Legend_flow::Horizontal) {
		total_h = fnt_sz;
	} else {
		total_h = fnt_sz * leg.size();
		total_h += (leg.size() > 1) ? (leg.size() - 1) * pad_v : 0;
	}
	return total_h + pad_v * 2;
}

//------------------------------------------------------------------------------

int chart::Legend_box::valid_pad(int p) const
{
	if (p < min_padding || p > max_padding) {
		throw std::runtime_error("Invalid padding value");
	}
	return p;
}

int chart::Legend_box::valid_fnt_sz(int sz) const
{
	if (sz < min_font_size || sz > max_font_size) {
		throw std::runtime_error("Invalid font size");
	}
	return sz;
}

void chart::Legend_box::draw_frame() const
{
	if (!fill_color().visibility() && !color().visibility()) {
		return;
	}
	int width = calc_w();
	int height = calc_h();
	Graph_lib::Color ocol = fl_color();
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_rectf(top_left_corner().x, top_left_corner().y, width, height);
	}
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_rect(top_left_corner().x, top_left_corner().y, width, height);
	}
	fl_color(ocol.as_int());
}

void chart::Legend_box::draw_swatch(Graph_lib::Point xy,
                                    Graph_lib::Color color,
                                    int width,
                                    int height) const
{
	Graph_lib::Color ocol = fl_color();
	fl_color(color.as_int());
	fl_rectf(xy.x, xy.y, width, height);
	fl_color(ocol.as_int());
}

string chart::Legend_box::comb_lb() const
{
	std::string s;
	for (const Legend& l : leg) {
		s += l.label;
	}
	return s;
}

int chart::Legend_box::max_lb_w() const
{
	int max_w = 0;

	for (const Legend& l : leg) {
		max_w = (std::max)(max_w, ch15_hlp::calc_lb_w(l.label, fnt, fnt_sz));
	}
	return max_w;
}

int chart::Legend_box::num_shp() const
{
	int n = 0;
	for (const Legend& l : leg) {
		if (l.legend_type == Legend_type::Shape) {
			++n;
		}
	}
	return n;
}
