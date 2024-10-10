#ifndef BAR_CHART_H
#define BAR_CHART_H
#include "../../lib/Graph.h"
#include <string>

namespace barch {

class Bar_chart;

class Bar : public Graph_lib::Shape
{
public:
	Bar(const Bar_chart& parent_chart, const std::string& label, double value);
	void draw_lines() const override;
	int value() const { return val; };
	std::string label() const { return lb; };
	int ordered_index() const { return oid; };

	void set_ordered_index(int idx) { oid = idx; };

private:
	const Bar_chart& par;
	int oid; // ordered index
	double val;
	std::string lb;
	void draw_label(Graph_lib::Point min, int h) const;
	int top_l_x() const;
	int nudged_h() const;
};

enum class Order { Asc, Desc };
enum class Sign { Neg, Pos };

class Bar_chart : public Graph_lib::Shape
{
public:
	Bar_chart(Graph_lib::Point origin,
	          int width,
	          int height,
	          int bars_padding = 0);
	void add(const std::string& label, double value);
	void draw_lines() const override;

	void set_title(const std::string& s) { title = s; };
	void set_title_font_size(int sz) { title_fnt_sz = valid_fnt_sz(sz); };
	int title_font_size() const { return title_fnt_sz; };

	void set_x_title(const std::string& s) { x_title = s; };
	void set_x_title_font_size(int sz) { x_title_fnt_sz = valid_fnt_sz(sz); };
	int x_title_font_size() const { return x_title_fnt_sz; };

	void set_y_title(const std::string& s) { y_title = s; };
	void set_y_title_font_size(int sz) { x_title_fnt_sz = valid_fnt_sz(sz); };
	int y_title_font_size() const { return y_title_fnt_sz; };

	void set_min_value(double m);
	void set_max_value(double m);
	void unset_min_value() { use_usr_min_val = false; };
	void unset_max_value() { use_usr_max_val = false; };

	void show_grid_lines() { show_grid = true; };
	void hide_grid_lines() { show_grid = false; };

	void show_x_values() { show_x_vals = true; };
	void hide_x_values() { show_x_vals = false; };
	void show_y_values() { show_y_vals = true; };
	void hide_y_values() { show_y_vals = false; };

	void set_unit(double u)
	{
		notch_unit = valid_unit(u);
		upd_scale_y();
	};
	double unit() const { return notch_unit; }
	int notch_size() const { return notch_sz; };

	Graph_lib::Line_style style() const { return ls; }; /* hides base class */
	void set_style(Graph_lib::Line_style s);            /*     methods      */

	void set_colors(std::initializer_list<Graph_lib::Color> cv);
	void set_fill_colors(std::initializer_list<Graph_lib::Color> cv);
	Graph_lib::Color color_by_index(int n) const;
	Graph_lib::Color fill_color_by_index(int n) const;

	Graph_lib::Point bars_origin() const;
	int number_of_bars() const { return bars.size(); }
	int bar_width() const { return static_cast<int>(scale_x); }
	int bars_padding() const { return pad_bars; }
	double y_scale_factor() const { return scale_y; };

	void sort_by_label(Order o = Order::Asc);
	void sort_by_value(Order o = Order::Asc);

	Graph_lib::Font x_value_font() const { return x_val_fnt; };
	void set_x_value_font(Graph_lib::Font f) { x_val_fnt = f; };

	int x_value_font_size() const { return x_val_fnt_sz; };
	void set_x_value_font_size(int size) { x_val_fnt_sz = size; };

	void show_frame() { show_fr = true; };
	void hide_frame() { show_fr = false; };

	int notch_nudge_distance(Sign s) const
	{
		return (s == Sign::Neg) ? n_nudge_neg : n_nudge_pos;
	};
	int last_nudged_notch(Sign s) const
	{
		return (s == Sign::Neg) ? n_nudge_neg_until : n_nudge_pos_until;
	};

private:
	// Dimensions, padding
	int h;
	int w;
	bool auto_pad_bars;
	int pad_bars;
	int pad_h;
	int pad_v;
	int y_w;

	// Font size
	int title_fnt_sz;
	int x_title_fnt_sz;
	int y_title_fnt_sz;
	int x_val_fnt_sz;
	int y_val_fnt_sz;

	// Value ranges, scaling
	double min_val;
	double max_val;
	bool use_usr_min_val;
	bool use_usr_max_val;
	double usr_min_val;
	double usr_max_val;
	double scale_x;
	double scale_y;

	// Notch settings
	int notch_sz;
	double notch_unit;
	int notch_w;
	int n_nudge_neg;
	int n_nudge_neg_until;
	int n_nudge_pos;
	int n_nudge_pos_until;

	// Visibility toggles
	bool show_grid;
	bool show_title;
	bool show_x_title;
	bool show_y_title;
	bool show_x_vals;
	bool show_y_vals;
	bool show_fr;

	// Appearance
	Graph_lib::Line_style ls; // hides base class Line_style
	Graph_lib::Font title_fnt;
	Graph_lib::Font y_val_fnt;
	Graph_lib::Font x_val_fnt;
	Graph_lib::Font y_title_fnt;
	Graph_lib::Font x_title_fnt;
	std::vector<Graph_lib::Color> color;
	std::vector<Graph_lib::Color> fill;

	// Title strings
	std::string title;
	std::string x_title;
	std::string y_title;

	Graph_lib::Vector_ref<Bar> bars;

	void draw_title() const;
	void draw_x_title() const;
	void draw_y_axis() const;
	void draw_y_val(Graph_lib::Point xy, double val) const;
	void draw_y_title() const;

	int calc_top_h() const;
	int calc_btm_h() const;
	int calc_graph_h() const;
	int calc_y_axis_w() const;
	void upd_y_w();
	void upd_min_max_val();
	void upd_scale_x();
	void upd_scale_y();
	void upd_colors();
	void upd_ln_style();
	void upd_notch_sz();
	void upd_pad_bars();

	void upd_n_nudge(Sign s);
	// Calculates and stores the distance to nudge notches,
	// and the number of notches to nudge.
	// Notches are nudged by x amount of pixels for the
	// height of the Y-axis to fit exactly to the desired
	// bounds. Affects both the axis AND height of the Bars.

	// Validates, throws if invalid
	int valid_fnt_sz(const int sz) const;
	double valid_unit(const double u) const;
	int valid_pad_bars(int p) const;
};

} // namespace barch

#endif // BAR_CHART_H
