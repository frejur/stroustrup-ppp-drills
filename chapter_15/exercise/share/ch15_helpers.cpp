#include "ch15_helpers.h"
#include "bar_chart.h"
#include "nval_pair.h"

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

void ch15_hlp::add_name_value_pairs_from_file(barch::Bar_chart& bar_chart,
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
