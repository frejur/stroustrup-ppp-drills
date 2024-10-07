#include "bar_chart.h"
#include "ch15_helpers.h"

barch::Bar::Bar(const Bar_chart& parent_chart, const string& label, double value)
    : par(parent_chart)
    , oid(par.number_of_bars())
    , val(value)
    , lb(label)
{}

void barch::Bar::draw_label(Graph_lib::Point bar_origin, int bar_height) const
{
	int y_offs = (val >= 0) ? bar_height + par.x_value_font_size() * 2
	                        : -par.x_value_font_size();
	int w = ch15_hlp::calc_lb_w(label(),
	                            par.x_value_font(),
	                            par.x_value_font_size());
	int x_offs = static_cast<int>(std::round(par.bar_width() * 0.5 - w * 0.5));
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(par.x_value_font().as_int(), par.x_value_font_size());
	fl_draw(lb.c_str(), bar_origin.x + x_offs, bar_origin.y + y_offs);
	fl_font(ofnt, osz);
}

int barch::Bar::top_l_x() const
{
	int bar_top_left_x{par.bars_origin().x};
	bar_top_left_x += par.bars_padding() + par.bar_width() * oid
	                  + par.bars_padding() * oid;
	return bar_top_left_x;
}

int barch::Bar::nudged_h() const
{
	double precise_h = std::abs(par.y_scale_factor() * val);
	double num_notches{precise_h / (par.y_scale_factor() * par.unit())};
	int min_num_notches{static_cast<int>(num_notches)};
	double notches_diff_f{num_notches - min_num_notches};

	int dist_to_closest{min_num_notches * par.notch_size()};
	int dist_to_after_closest{dist_to_closest + par.notch_size()};
	int last_nudged = (val >= 0) ? par.last_nudged_notch(Sign::Pos)
	                             : par.last_nudged_notch(Sign::Neg);
	int nudge_count_closest = (std::min)(min_num_notches, last_nudged);
	int nudge_count_after = (std::min)(min_num_notches + 1, last_nudged);
	int nudge_dist_closest = (val >= 0)
	                             ? nudge_count_closest
	                                   * par.notch_nudge_distance(Sign::Pos)
	                             : nudge_count_closest
	                                   * par.notch_nudge_distance(Sign::Neg);
	int nudge_dist_after = (val >= 0)
	                           ? nudge_count_after
	                                 * par.notch_nudge_distance(Sign::Pos)
	                           : nudge_count_after
	                                 * par.notch_nudge_distance(Sign::Neg);
	int nudge_dist_delta = (dist_to_after_closest + nudge_dist_after)
	                       - (dist_to_closest + nudge_dist_closest);
	int nudge_diff{
	    static_cast<int>(std::round(notches_diff_f * nudge_dist_delta))};
	return min_num_notches * par.notch_size() + nudge_dist_closest + nudge_diff;
}

void barch::Bar::draw_lines() const
{
	if (val == 0 || (!fill_color().visibility() && !color().visibility())) {
		return;
	}

	int h{nudged_h()};
	int tl_x{top_l_x()};
	int tl_y = (val > 0) ? par.bars_origin().y - h : par.bars_origin().y;

	if (fill_color().visibility()) { // fill
		fl_color(fill_color().as_int());
		fl_rectf(tl_x, tl_y, par.bar_width(), h);
	}

	if (color().visibility()) { // lines on top of fill
		fl_color(color().as_int());
		fl_rect(tl_x, tl_y, par.bar_width(), h);
	}

	draw_label({tl_x, tl_y}, h);
}
