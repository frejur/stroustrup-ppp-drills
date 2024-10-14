#include "ch15_helpers.h"
#include "chart/bar_chart.h"
#include "parse/nval_pair.h"

int ch15_hlp::calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz)
{
	int dummy; // not needed
	int w;
	int font_backup = fl_font();
	int size_backup = fl_size();
	fl_font(f.as_int(), f_sz);
	fl_text_extents(txt.c_str(), dummy, dummy, w, dummy);
	fl_font(font_backup, size_backup);
	return w;
}

void ch15_hlp::add_name_value_pairs_from_file(chart::Bar_chart& bar_chart,
                                              const std::string& filename)
{
	std::ifstream ifs{filename};
	if (!ifs) {
		throw std::runtime_error("Could not open file: '" + filename + "'");
	}

	Name_value_pair p;
	while (ifs >> p) {
		bar_chart.add(p.name, p.value);
	}
}

void ch15_hlp::draw_text(Graph_lib::Point xy,
                         const string& text,
                         Graph_lib::Font font,
                         int font_size,
                         Graph_lib::Color text_color,
                         Text_alignment alignment,
                         int px_offset)
{
	if (text.empty()) {
		return;
	}
	int ofnt = fl_font();
	int osz = fl_size();
	int ocol = fl_color();
	fl_font(font.as_int(), font_size);
	fl_color(text_color.as_int());
	int offs_x = 0;
	int offs_y = 0;
	if (alignment == Text_alignment::Right) {
		offs_x = px_offset;
		offs_y = static_cast<int>(std::round(font_size * 0.5));
	} else {
		int w = calc_lb_w(text, font, font_size);
		if (alignment == Text_alignment::Left) {
			offs_x = -(w + px_offset);
		} else {
			offs_x = -(static_cast<int>(std::round(w * 0.5)));
		}

		if (alignment == Text_alignment::Top) {
			offs_y = -(font_size + px_offset);
		} else if (alignment == Text_alignment::Bottom) {
			offs_y = font_size + px_offset;
		}
	}
	fl_draw(text.c_str(), xy.x + offs_x, xy.y - fl_descent() + offs_y);
	fl_font(ofnt, osz);
	fl_color(ocol);
}
