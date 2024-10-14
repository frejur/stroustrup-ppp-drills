#include "elem.h"
#include "../ch15_helpers.h"
#include "chart.h"

chart::Chart_element::Chart_element(const Chart& parent_chart,
                                    const string& label,
                                    double x_value,
                                    double y_value)
    : par(parent_chart)
    , x_val(x_value)
    , y_val(y_value)
    , lb(label)
{}

void chart::Chart_element::draw_label() const
{
	Graph_lib::Point xy{par.position_from_value(x_val, y_val)};
	Graph_lib::Point offs{label_offset()};
	ch15_hlp::draw_text({xy.x + offs.x, xy.y + offs.y},
	                    lb.c_str(),
	                    par.label_font().as_int(),
	                    par.label_font_size(),
	                    par.label_color(),
	                    par.label_alignment(),
	                    par.label_padding());
}
