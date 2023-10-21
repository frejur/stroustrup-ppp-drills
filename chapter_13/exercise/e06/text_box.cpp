#include "text_box.h"
#include <iostream>
#include "box.h"
#include <typeinfo>

using namespace TBX;

Text_box::Text_box(GL::Point xy, const string& text, BG_shape bg)
: Text(xy, text), c_mark(std::make_unique<GL::Lines>())
{
	set_font_size(default_font_size);
	set_font(default_font_face);
	set_color(default_font_color);

	std::pair<int, int> text_sz{ get_bbox_size() };

	// Hack: Add underscore to force extend text height, use as standard height
	std::pair<int, int> text_ext_h{ get_bbox_size(text + "_") };

	// Center text
	move(
		-1 * static_cast<int>(text_sz.first * 0.5),
		static_cast<int>(text_sz.second * 0.25) // Note offset
	);
	bg_shape = init_bg_shape(bg, text_sz.first, text_ext_h.second);
	set_bg_shape_color(default_font_color);

	c_mark->add({xy.x, xy.y - 5}, {xy.x, xy.y + 5});
	c_mark->add({xy.x - 5, xy.y}, {xy.x + 5, xy.y});

	std::cout << "Size: " << text_sz.first << ", "
		<< text_sz.second << std::endl;
}

std::pair<int, int> Text_box::get_bbox_size(const string &s) const {
	int mv_x = 0, mv_y = 0, sz_x = 0, sz_y = 0;
	Fl_Font old_font{ fl_font() };
	Fl_Fontsize old_sz{ fl_size() };
	fl_font(font().as_int(), font_size());
	if (s.empty()) {
		fl_text_extents(label().c_str(), mv_x, mv_y, sz_x, sz_y);
	} else {
		fl_text_extents(s.c_str(), mv_x, mv_y, sz_x, sz_y);
	}
	fl_font(old_font, old_sz);
	return std::pair<int, int>(sz_x, sz_y);
}

std::unique_ptr<GL::Shape> Text_box::init_bg_shape(BG_shape bg, int ww, int hh)
{
	switch(bg) {
	case BG_BOX:
	{
		int pad{ static_cast<int>(font_size() * 0.25) };
		int h_nudge{ static_cast<int>(hh * 0.15 ) };
		GL::Point o{ point(0).x - pad, point(0).y - hh - pad + h_nudge };
		return std::make_unique<BOX::Box>(o, ww + pad * 2, hh + pad * 2, 0.8);
	}
	case BG_ELLIPSE:
	{
		int w_half{ static_cast<int>(ww * 0.5) };
		int h_half{ static_cast<int>(hh * 0.5) };
		int h_nudge{ static_cast<int>(hh * 0.15 ) };
		int pad{ static_cast<int>(font_size() * 0.5) };
		GL::Point o{ point(0).x + w_half, point(0).y - h_half + h_nudge};
		return std::make_unique<GL::Ellipse>(o, w_half + pad, h_half + pad);
	}
	default:
		return std::unique_ptr<GL::Shape>();
	}
}

void Text_box::set_bg_shape_color(GL::Color c) {
	if (bg_shape) {
		bg_shape->set_color(c);
	}
}

void Text_box::set_fill_color(GL::Color c) {
	if (bg_shape) {
		bg_shape->set_fill_color(c);
	}
}
void Text_box::draw_lines() const{
	if (bg_shape) {
		if (typeid(*bg_shape.get()) == typeid(BOX::Box)) {
			dynamic_cast<BOX::Box*>(bg_shape.get())->draw_lines();
		}else if (typeid(*bg_shape.get()) == typeid(GL::Ellipse)) {
			dynamic_cast<GL::Ellipse*>(bg_shape.get())->draw_lines();
		}
	}
	Text::draw_lines();
	c_mark->draw_lines();
}
