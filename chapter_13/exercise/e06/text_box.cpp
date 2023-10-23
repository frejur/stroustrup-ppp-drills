#include "text_box.h"
#include <iostream>
#include "box.h"
#include <typeinfo>

using namespace TBX;

Text_box::Text_box(GL::Point xy, const string& text, BG_shape bg)
	: Text(xy, text), c(xy), bg_type(bg), c_mark(std::make_unique<GL::Lines>())
{
	set_font_size(default_font_size);
	set_font(default_font_face);
	set_color(default_font_color);

	std::pair<int, int> text_sz{ get_bbox_size() };

	// Hack: Add underscore to force extend text height, use as standard height
	std::pair<int, int> text_ext_h{ get_bbox_size(text + "_") };

	text_w = text_sz.first;
	text_h = text_ext_h.second;

	// Center text
	move(
		-1 * static_cast<int>(text_sz.first * 0.5),
		static_cast<int>(text_sz.second * 0.25) // Note offset
	);
	h_nudge =	(bg_type == BG_ELLIPSE)
				? static_cast<int>(text_h * 0.15 )
				: 0;
	bg_shape = init_bg_shape(bg, text_w, text_h);
	set_bg_shape_color(default_font_color);
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
		GL::Point o{ point(0).x - pad, point(0).y - hh - pad + h_nudge };
		return std::make_unique<BOX::Box>(o, ww + pad * 2, hh + pad * 2, 0.8);
	}
	case BG_ELLIPSE:
	{
		int w_half{ static_cast<int>(ww * 0.5) };
		int h_half{ static_cast<int>(hh * 0.5) };
		int pad{ static_cast<int>(font_size() * 0.5) };
		GL::Point o{ point(0).x + w_half, point(0).y - h_half + h_nudge};
		return std::make_unique<GL::Ellipse>(o, w_half + pad, h_half + pad);
	}
	default:
		return std::unique_ptr<GL::Shape>();
	}
}

int Text_box::corner_radius() const{
	if (!bg_shape || typeid(*bg_shape.get()) != typeid(BOX::Box)) {
		return 0;
	}
	return dynamic_cast<BOX::Box*>(bg_shape.get())->corner_radius();
}

void Text_box::set_color(GL::Color c) {
	Shape::set_color(c);
	set_bg_shape_color(c);
}

void Text_box::set_style(GL::Line_style s) {
	Shape::set_style(s);
}

void Text_box::set_bg_shape_color(GL::Color c) {
	if (bg_shape) {
		bg_shape->set_color(c);
	}
}
int Text_box::width() const
{
	if (bg_shape) {
		if (typeid(*bg_shape.get()) == typeid(BOX::Box)) {
			return dynamic_cast<BOX::Box*>(bg_shape.get())->width();
		}else if (typeid(*bg_shape.get()) == typeid(GL::Ellipse)) {
			return dynamic_cast<GL::Ellipse*>(bg_shape.get())->major() * 2;
		}
	}
	return text_w;
}

int Text_box::height() const
{
	if (bg_shape) {
		if (typeid(*bg_shape.get()) == typeid(BOX::Box)) {
			return dynamic_cast<BOX::Box*>(bg_shape.get())->height();
		}else if (typeid(*bg_shape.get()) == typeid(GL::Ellipse)) {
			return dynamic_cast<GL::Ellipse*>(bg_shape.get())->minor() * 2;
		}
	}
	return text_h;
}

GL::Point Text_box::bbox_origin() const
{
	if (bg_shape) {
		if (typeid(*bg_shape.get()) == typeid(BOX::Box)) {
			return dynamic_cast<BOX::Box*>(bg_shape.get())->bbox_origin();
		}else if (typeid(*bg_shape.get()) == typeid(GL::Ellipse)) {
			return dynamic_cast<GL::Ellipse*>(bg_shape.get())->point(0);
		}
	}
	return {
		c.x - static_cast<int>(text_w * 0.5), c.y -
		static_cast<int>(text_h * 0.5)
	};
}

GL::Point Text_box::bbox_point(int p) const {
	if (bg_shape) {
		if (typeid(*bg_shape.get()) == typeid(BOX::Box)) {
			return dynamic_cast<BOX::Box*>(bg_shape.get())->point(p);
		}else if (typeid(*bg_shape.get()) == typeid(GL::Ellipse)) {
			return dynamic_cast<GL::Ellipse*>(bg_shape.get())->point(0);
		}
	}
	return {
		c.x - static_cast<int>(text_w * 0.5),
		c.y - static_cast<int>(text_h * 0.5)
	};
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
//	c_mark->draw_lines();
}
