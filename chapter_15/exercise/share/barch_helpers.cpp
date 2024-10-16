#include "barch_helpers.h"
#include "chart/bar_chart.h"
#include "parse/nval_pair.h"

void barch_hlp::add_name_value_pairs_from_file(chart::Bar_chart& bar_chart,
                                               const std::string& filename)
{
	std::ifstream ifs{filename};
	if (!ifs) {
		throw std::runtime_error("Could not open file: '" + filename + "'");
	}

	bar_chart.disable_automatic_refresh();
	Name_value_pair p;
	while (ifs >> p) {
		bar_chart.add(p.name, p.value);
	}
	bar_chart.enable_automatic_refresh();
	bar_chart.refresh();
}
