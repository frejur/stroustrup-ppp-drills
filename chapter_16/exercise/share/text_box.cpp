#include "ch16_helpers.h"
#include "shape_button.h"

shp_btn::Text_box::Text_box(Graph_lib::Point top_left,
                            int w,
                            int h,
                            const string& label)
    : is_hidden(false)
    , lb(label)
{
	if (h <= 0 || w <= 0) {
		throw std::runtime_error("Bad rectangle: non-positive side");
	}
	add(top_left);
	add({top_left.x + w, top_left.y + h});
}

//------------------------------------------------------------------------------

void shp_btn::Text_box::transform(Graph_lib::Point top_left,
                                  Graph_lib::Point bottom_right)
{
	if ((bottom_right.x - top_left.x) <= 0
	    || (bottom_right.y - top_left.y) <= 0) {
		throw std::runtime_error("Bad rectangle: first point is not top left");
	}
	set_point(0, top_left);
	set_point(1, bottom_right);
}

void shp_btn::Text_box::draw_lines() const
{
	if (is_hidden
	    || (!color().visibility() && !fill_color().visibility()
	        && label().size() == 0)) {
		return;
	}

	int w = (point(1).x - point(0).x);
	int h = (point(1).y - point(0).y);

	if (fill_color().visibility()) { // fill
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x, point(0).y, w, h);
	}

	if (color().visibility()) { // lines on top of fill
		fl_color(color().as_int());
		fl_rect(point(0).x, point(0).y, w, h);
	}

	if (label().size() > 0) {
		int ofnt = fl_font();
		int osz = fl_size();
		fl_font(fnt.as_int(), fnt_sz);

		Graph_lib::Point c{
		    point(0).x
		        + static_cast<int>(std::round((point(1).x - point(0).x) * 0.5)),
		    point(0).y
		        + static_cast<int>(std::round((point(1).y - point(0).y) * 0.5)),
		};
		ch16_hlp::draw_text(c,
		                    label(),
		                    font(),
		                    font_size(),
		                    color(),
		                    ch16_hlp::Text_alignment::Center);
		fl_font(ofnt, osz);
	}
}
