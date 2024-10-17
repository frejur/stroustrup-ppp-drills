#ifndef CHART_H
#define CHART_H
#include "../../../lib/Graph.h"
#include "canvas.h"

namespace ch15_hlp {
enum class Text_alignment; // Forward declare
}

namespace chart {

class Chart_element; // Forward declare

class Chart : public Graph_lib::Shape
{
public:
	// Position
	Graph_lib::Point top_left_corner() const { return point(0); };
	Graph_lib::Point canvas_top_left_corner() const
	{
		return cv.top_left_corner();
	};
	Graph_lib::Point origin() const { return cv.origin(); };
	Graph_lib::Point position_from_value(long double x, long double y) const
	{
		return cv.position_from_value(x, y);
	};

	// Values
	void set_x_min_value(long double m);
	void set_x_max_value(long double m);
	void set_y_min_value(long double m);
	void set_y_max_value(long double m);
	void unset_x_min_value();
	void unset_x_max_value();
	void unset_y_min_value();
	void unset_y_max_value();

	// Toggle visibility
	void show_horizontal_grid_lines() { cv.show_horizontal_grid_lines(); };
	void hide_horizontal_grid_lines() { cv.hide_horizontal_grid_lines(); };
	void show_vertical_grid_lines() { cv.show_vertical_grid_lines(); };
	void hide_vertical_grid_lines() { cv.hide_vertical_grid_lines(); };
	void show_x_values() { cv.show_x_values(); };
	void hide_x_values() { cv.hide_x_values(); };
	void show_y_values() { cv.show_y_values(); };
	void hide_y_values() { cv.hide_y_values(); };
	void show_frame() { show_fr = true; };
	void hide_frame() { show_fr = false; };
	void show_labels() { show_lb = true; };
	void hide_labels() { show_lb = false; };

	// Titles appearance
	void set_title(const std::string& s) { title = s; };
	void set_title_font_size(int sz) { title_fnt_sz = valid_fnt_sz(sz); };
	int title_font_size() const { return title_fnt_sz; };
	void set_x_title(const std::string& s) { x_title = s; };
	void set_x_title_font_size(int sz) { x_title_fnt_sz = valid_fnt_sz(sz); };
	int x_title_font_size() const { return x_title_fnt_sz; };
	void set_y_title(const std::string& s) { y_title = s; };
	void set_y_title_font_size(int sz) { x_title_fnt_sz = valid_fnt_sz(sz); };
	int y_title_font_size() const { return y_title_fnt_sz; };

	// Values appearance
	Graph_lib::Font x_value_font() const { return cv.x_value_font(); };
	void set_x_value_font(Graph_lib::Font f) { cv.set_x_value_font(f); };
	int x_value_font_size() const { return cv.x_value_font_size(); };
	void set_x_value_font_size(int size) { cv.set_x_value_font_size(size); };
	Graph_lib::Font y_value_font() const { return cv.y_value_font(); };
	void set_y_value_font(Graph_lib::Font f) { cv.set_y_value_font(f); };
	int y_value_font_size() const { return cv.y_value_font_size(); };
	void set_y_value_font_size(int size) { cv.set_y_value_font_size(size); };

	// Label appearance
	void set_label_color(Graph_lib::Color c) { lb_color = c; };
	void set_label_font(Graph_lib::Font f) { lb_fnt = f; };
	void set_label_font_size(int sz) { lb_fnt_sz = sz; };
	Graph_lib::Color label_color() const { return lb_color; };
	Graph_lib::Font label_font() const { return lb_fnt; };
	int label_font_size() const { return lb_fnt_sz; };
	virtual ch15_hlp::Text_alignment label_alignment() const;
	virtual int label_padding() const { return pad_h; };

	// Units and scaling
	double x_scale_factor() const { return cv.x_scale_factor(); };
	double y_scale_factor() const { return cv.y_scale_factor(); };
	double x_unit() const { return cv.x_unit(); };
	double y_unit() const { return cv.y_unit(); };
	void set_x_unit(double u) { cv.set_x_unit(u); };
	void set_y_unit(double u) { cv.set_y_unit(u); };

	void draw_lines() const override;

	// Refresh
	void enable_automatic_refresh() { enable_refr = true; };
	void disable_automatic_refresh() { enable_refr = false; };
	void refresh()
	{
		if (enable_refr) {
			upd_min_max_val();
			upd_layout();
			cv.refresh();
		}
	};

private:
	struct Min_max_vals
	{
		long double x_min{0};
		long double x_max{0};
		long double y_min{0};
		long double y_max{0};
	};
	enum class Upd_state;

protected:
	Chart(Graph_lib::Point top_left, int width, int height);

	// Dimensions, padding
	int h;
	int w;
	int pad_h;
	int pad_v;
	int pad_graph_btm;
	int left_block_w;

	int right_block_w;
	int upper_block_h;
	int lower_block_h;

	// Font size
	int title_fnt_sz;
	int x_title_fnt_sz;
	int y_title_fnt_sz;
	int lb_fnt_sz;

	// Value ranges, scaling
	Min_max_vals usr_min_max;
	bool use_usr_x_min_val;
	bool use_usr_x_max_val;
	bool use_usr_y_min_val;
	bool use_usr_y_max_val;

	// Visibility toggles
	bool show_fr;
	bool show_lb;

	// Toggle refresh
	bool enable_refr;

	// Appearance
	Graph_lib::Line_style ls; // hides base class Line_style
	Graph_lib::Font title_fnt;
	Graph_lib::Font y_title_fnt;
	Graph_lib::Font x_title_fnt;
	Graph_lib::Font lb_fnt;
	Graph_lib::Color lb_color;

	// Title strings
	std::string title;
	std::string x_title;
	std::string y_title;

	// Canvas
	Canvas cv;

	// Graph elements
	Graph_lib::Vector_ref<Chart_element> elem;

	Upd_state layout_upd_state;

	void draw_title() const;
	void draw_x_title() const;
	void draw_y_title() const;
	void draw_graph() const;

	// Update layout
	void upd_layout(); // Calls the methods listed below in sequential order
	void upd_left_block();
	void upd_right_block();
	void upd_upper_block();
	void upd_lower_block();
	void upd_graph();
	virtual void upd_post_layout(){}; // Can be overriden to perform actions
	                                  // after the layout has been updated

	void upd_min_max_val();
	Min_max_vals min_max_vals_from_elements() const;

	int valid_fnt_sz(const int sz) const;
	void validate_current_upd_state(
	    std::initializer_list<Upd_state> expected) const;
	void validate_current_upd_state(Upd_state expected) const
	{
		validate_current_upd_state({expected});
	};
};

enum class Chart::Upd_state {
	None,
	Left_block_done,
	Right_block_done,
	Upper_block_done,
	Lower_block_done,
	Graph_done,
	All_done
};

//------------------------------------------------------------------------------

enum class Point_shape_type { Point, Circle, Diamond };
void draw_plot_point(Graph_lib::Point xy, Point_shape_type t, int pt_sz);

//------------------------------------------------------------------------------

} // namespace chart

#endif // CHART_H
