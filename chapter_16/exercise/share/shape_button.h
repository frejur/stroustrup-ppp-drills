#ifndef SHAPE_BUTTON_H
#define SHAPE_BUTTON_H

#include "../../lib/GUI.h"
#include "../../lib/Graph.h"
#include <string>

namespace shp_btn {

enum class Shape_button_state { Normal, Active, Disabled };

class Control : public Graph_lib::Button
{
public:
	using Graph_lib::Button::Button;
	virtual bool is_visible() const { return pw->visible(); };
};

class Text_box : public Graph_lib::Shape
{
public:
	Text_box(Graph_lib::Point top_left, int w, int h, const std::string& label);
	void transform(Graph_lib::Point top_left, Graph_lib::Point bottom_right);

	// Visibility
	bool is_visible() const { return !is_hidden; };
	void hide() { is_hidden = true; };
	void show() { is_hidden = false; };

	// Label
	enum class Alignment { Left, Center, Right };
	std::string label() const { return lb; }
	Graph_lib::Font font() const { return fnt; }
	int font_size() const { return fnt_sz; }
	void set_label(const string& s) { lb = s; }
	void set_font(Graph_lib::Font f) { fnt = f; }
	void set_font_size(int s) { fnt_sz = s; }
	void set_alignment(Alignment a) { align = a; };

	virtual void draw_lines() const override;

private:
	bool is_hidden;
	int fnt_sz{fl_size() < 14 ? 14 : fl_size()};
	Graph_lib::Font fnt{fl_font()};
	std::string lb;
	Alignment align;
};

class Shape_button : public Control
{
public:
	Shape_button(Graph_lib::Point top_left,
	             int width,
	             int height,
	             const string& label,
	             Graph_lib::Callback callback_fn,
	             Graph_lib::Color bg_color = default_fill_color());

	Shape_button(Graph_lib::Point top_left,
	             int normal_width,
	             int normal_height,
	             int active_width,
	             int active_height,
	             const string& label,
	             Graph_lib::Callback callback_fn,
	             Graph_lib::Color bg_color = default_fill_color());

	Graph_lib::Point position() const
	{
		return is_active() ? active_xy : normal_xy;
	};
	int width() const { return is_active() ? active_w : normal_w; };
	int height() const { return is_active() ? active_h : normal_h; };

	// Widget
	virtual void move(int offs_x, int offs_y) override;
	virtual void hide() override;
	virtual void show() override;
	virtual void attach(Graph_lib::Window&) override;
	void offset_active_position(int offs_x, int offs_y);
	void offset_normal_position(int offs_x, int offs_y);

	// Shape
	Graph_lib::Color color() const { return box.color(); };
	virtual Graph_lib::Color fill_color() const { return box.fill_color(); };
	Graph_lib::Line_style style() const { return box.style(); };
	void set_color(Graph_lib::Color col) { box.set_color(col); };
	virtual void set_fill_color(Graph_lib::Color col)
	{
		box.set_fill_color(col);
	};
	void set_style(Graph_lib::Line_style sty) { box.set_style(sty); };
	void reset_color() { box.set_color(reset_col); };
	void reset_fill_color() { box.set_fill_color(reset_fill); };
	void reset_style() { box.set_style(reset_sty); };

	// Label
	std::string label() const { return box.label(); };
	Graph_lib::Font font() const { return box.font(); };
	int font_size() const { return box.font_size(); };
	void set_label(const string& s) { box.set_label(s); };
	void set_font(Graph_lib::Font f) { box.set_font(f); };
	void set_font_size(int s) { box.set_font_size(s); };
	void reset_label() { box.set_label(reset_lb); };
	void reset_font() { box.set_font(reset_fnt); };
	void reset_font_size() { box.set_font_size(reset_fnt_sz); };
	void set_alignment(Text_box::Alignment a) { box.set_alignment(a); };

	// Update defaults
	void set_current_color_as_default() { reset_col = box.color(); };
	void set_current_fill_color_as_default() { reset_fill = box.fill_color(); };
	void set_current_style_as_default() { reset_sty = style(); }
	void set_current_font_as_default() { reset_fnt = font(); }
	void set_current_font_size_as_default() { reset_fnt_sz = font_size(); }
	void set_current_label_as_default() { reset_lb = label(); }
	void set_current_as_default()
	{
		set_current_color_as_default();
		set_current_fill_color_as_default();
		set_current_style_as_default();
		set_current_font_as_default();
		set_current_font_size_as_default();
		set_current_label_as_default();
	};

	// State
	bool is_normal() const;
	bool is_active() const;
	bool is_disabled() const;
	virtual bool is_visible() const override;
	virtual void normalize();
	virtual void activate();
	virtual void disable();
	bool is_not_attached() const { return !is_attached; }

	virtual void put_on_top();

protected:
	Text_box box;    // Covers buttons, dictates appearance
	Control btn_act; // Active

private:
	bool is_hidden;
	bool is_attached;

	Shape_button_state st;
	Graph_lib::Point normal_xy;
	Graph_lib::Point active_xy;
	Graph_lib::Color reset_col;
	Graph_lib::Color reset_fill;
	Graph_lib::Line_style reset_sty;

	int reset_fnt_sz;
	std::string reset_lb;
	Graph_lib::Font reset_fnt;

	const int normal_w;
	const int normal_h;
	const int active_w;
	const int active_h;

	Shape_button_state state() const { return st; };

	static const Graph_lib::Color& default_fill_color();

	void require_attached() const
	{
		if (!is_attached) {
			throw std::runtime_error(
			    "This operation may not be carried out in an unattached state");
		}
	}
};

} // namespace shp_btn

#endif // SHAPE_BUTTON_H
