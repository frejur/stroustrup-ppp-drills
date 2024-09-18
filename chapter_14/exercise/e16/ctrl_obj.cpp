#include "ctrl_obj.h"
#include "../share/help/helpers.h"

void ch14_e16::Level_indicator::draw_lines() const
{
	Graph_lib::Circle::draw_lines();

	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(Graph_lib::Font::courier_bold, radius() * 2);
	fl_draw(label.c_str(),
	        center().x - static_cast<int>(radius() * 0.6),
	        center().y + static_cast<int>(radius() * 0.6));
	fl_font(ofnt, osz);
}

//------------------------------------------------------------------------------

void ch14_e16::Action_button::set_label(const string& s)
{
	label = s;
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), height());
	int dummy;
	int sz_x;
	fl_text_extents(s.c_str(), dummy, dummy, sz_x, dummy);
	fl_font(ofnt, osz);
	updateSize(txt_pad() * 2 + sz_x, height());
}

void ch14_e16::Action_button::draw_lines() const
{
	BOX::Box::draw_lines();

	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), height());
	fl_draw(label.c_str(),
	        bbox_origin().x + txt_pad(),
	        bbox_origin().y + static_cast<int>(height() * 0.75));
	fl_font(ofnt, osz);
}

bool ch14_e16::Action_button::point_is_on_button(Graph_lib::Point pt) const
{
	int r = corner_radius();
	Graph_lib::Point o = bbox_origin();

	if (pt.x < o.x || pt.x > o.x + width() || pt.y < o.y
	    || pt.y > o.y + height()) {
		return false;
	}

	Graph_lib::Point nw = {o.x + r, o.y + r};
	Graph_lib::Point ne = {o.x + width() - r, nw.y};
	Graph_lib::Point sw = {nw.x, o.y + height() - r};
	Graph_lib::Point se = {ne.x, sw.y};
	if (((pt.x > nw.x && pt.x < ne.x) && (pt.y >= o.y || pt.y <= o.y + height()))
	    || ((pt.x >= o.x && pt.x <= o.x + width())
	        && (pt.y > nw.y && pt.y > sw.y))) {
		return true;
	}

	if (ch14_hlp::distance_between(pt, nw) <= corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, ne) <= corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, se) <= corner_radius()) {
		return true;
	}
	if (ch14_hlp::distance_between(pt, sw) <= corner_radius()) {
		return true;
	}
	return false;
}
