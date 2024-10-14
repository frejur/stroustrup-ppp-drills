#ifndef CANVAS_H
#define CANVAS_H
#include "../../../lib/Graph.h"
#include <initializer_list>

namespace chart {

enum class Axis { X, Y };
enum class Sign { Neg, Pos };

class Canvas : Graph_lib::Shape
{
public:
	Canvas(Graph_lib::Point top_left, int width, int height);

	// Position
	Graph_lib::Point top_left_corner() const { return point(0); };
	Graph_lib::Point origin() const { return origin_; };
	Graph_lib::Point position_from_value(long double x, long double y) const;

	// Dimension
	int width() const { return w; };
	int height() const { return h; };
	void set_width(int w) { set_dimensions(w, height()); };
	void set_height(int h) { set_dimensions(width(), h); };
	void set_dimensions(int width, int height)
	{
		w = valid_w(width);
		h = valid_h(height);
		upd_layout();
	};

	// Values
	void set_x_min_value(double m);
	void set_x_max_value(double m);
	void set_y_min_value(double m);
	void set_y_max_value(double m);

	// Toggle visibility
	void show_horizontal_grid_lines() { show_x_grid = true; };
	void hide_horizontal_grid_lines() { show_x_grid = false; };
	void show_vertical_grid_lines() { show_y_grid = true; };
	void hide_vertical_grid_lines() { show_y_grid = false; };
	void show_x_axis_notches() { show_x_notches = true; };
	void hide_x_axis_notches() { show_x_notches = false; };
	void show_y_axis_notches() { show_y_notches = true; };
	void hide_y_axis_notches() { show_y_notches = false; };
	void show_x_values() { show_x_vals = true; };
	void hide_x_values() { show_x_vals = false; };
	void show_y_values() { show_y_vals = true; };
	void hide_y_values() { show_y_vals = false; };

	// Values appearance
	Graph_lib::Font x_value_font() const { return x_val_fnt; };
	void set_x_value_font(Graph_lib::Font f) { x_val_fnt = f; };
	int x_value_font_size() const { return x_val_fnt_sz; };
	void set_x_value_font_size(int size) { x_val_fnt_sz = size; };
	Graph_lib::Font y_value_font() const { return y_val_fnt; };
	void set_y_value_font(Graph_lib::Font f) { y_val_fnt = f; };
	int y_value_font_size() const { return y_val_fnt_sz; };
	void set_y_value_font_size(int size) { y_val_fnt_sz = size; };

	// Units and scaling
	double x_scale_factor() const { return scale_x; };
	double y_scale_factor() const { return scale_y; };
	double x_unit() const { return x_unit_; }
	double y_unit() const { return y_unit_; }
	void set_x_unit(double u);
	void set_y_unit(double u);

	// Notch nudging
	int notch_nudge_distance(Axis a, Sign s) const;
	int last_nudged_notch(Axis a, Sign s) const;

	// Colors and style
	void set_grid_color(Graph_lib::Color c) { grid_color = c; };
	void set_grid_style(Graph_lib::Line_style s) { grid_ls = s; };

	void refresh() { upd_layout(); };

	virtual void move(int offs_x, int offs_y) override
	{
		Graph_lib::Shape::move(offs_x, offs_y);
		upd_layout();
	};

	void draw_lines() const override;

private:
	struct Notch
	{
		int base_dist{0};
		int len{0};
		int neg_nudge_by{0};
		int pos_nudge_by{0};
		int neg_nudge_until{0};
		int pos_nudge_until{0};
	};
	enum class Upd_state;

protected:

	Graph_lib::Point origin_;

	// Dimensions, padding
	int w;
	int h;
	int pad_h;
	int pad_v;
	int x_ax_h;
	int y_ax_w;

	// Font size
	int x_val_fnt_sz;
	int y_val_fnt_sz;

	// Value ranges, scaling
	long double x_min_val;
	long double x_max_val;
	long double y_min_val;
	long double y_max_val;
	double x_unit_;
	double y_unit_;
	double scale_x;
	double scale_y;

	// Notches
	Notch x_notch;
	Notch y_notch;

	// Visibility toggles
	bool show_x_grid;
	bool show_y_grid;
	bool show_x_notches;
	bool show_y_notches;
	bool show_x_vals;
	bool show_y_vals;

	// Appearance
	Graph_lib::Font x_val_fnt;
	Graph_lib::Font y_val_fnt;
	Graph_lib::Line_style grid_ls;
	Graph_lib::Color grid_color;

	Upd_state layout_upd_state;

	void draw_x_axis() const;
	void draw_x_val(Graph_lib::Point xy, double val) const;
	void draw_y_axis() const;
	void draw_y_val(Graph_lib::Point xy, double val) const;

	int calc_x_axis_h() const;
	int calc_y_axis_w() const;
	int calc_y_vals_w() const;

	// Update layout
	void upd_layout(); // Calls the methods below sequentially
	void upd_x_ax_h();
	void upd_y_ax_w();
	void upd_origin();
	void upd_scale_x();
	void upd_scale_y();
	void upd_x_notch();
	void upd_y_notch();

	void upd_n_nudge(Axis a, Sign s);
	// Calculates and stores the distance by which to nudge axis notches,
	// and the number of notches to nudge.
	// Notches are nudged so that axes reach their exact target lengths in pixels.

	// Position (Tries to align with nudged notches)
	int val_to_px_offs(long double val, Axis a) const;

	// Draw stuff
	void draw_axis(Axis a) const;
	void draw_notch(int px_val, Axis a) const;
	void draw_grid_line(int px_val, Axis a) const;
	void draw_value(int val, int px_val, Axis a) const;

	// Validates, throws if invalid
	int valid_w(const int width) const;
	int valid_h(const int height) const;
	double valid_pad(const int p) const;
	long double valid_min(const long double max, const long double min) const;
	long double valid_max(const long double min, const long double max) const;
	double valid_unit(const double u) const;
	int valid_fnt_sz(const int sz) const;
	void validate_current_upd_state(
	    std::initializer_list<Upd_state> expected) const;
	void validate_current_upd_state(Upd_state expected) const
	{
		validate_current_upd_state({expected});
	};
};

enum class Canvas::Upd_state {
	None,
	X_axis_done,
	Y_axis_done,
	Origin_done,
	Scale_x_done,
	Scale_y_done,
	X_notch_done,
	Y_notch_done,
	All_done
};

} // namespace chart
#endif // CANVAS_H
