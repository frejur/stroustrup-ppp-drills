#include "text_box.h"
#include <iostream>
#include "box.h"

using namespace TBX;

Text_box::Text_box(GL::Point xy, const string& text, BG_shape bg)
: Text(xy, text), c_mark(std::make_unique<GL::Lines>())
{
	c_mark->add({xy.x, xy.y - 5}, {xy.x, xy.y + 5});
	c_mark->add({xy.x - 5, xy.y}, {xy.x + 5, xy.y});

	set_font_size(default_font_size);

	std::pair<int, int> text_sz{ get_bbox_size() };

	move(
		-1 * static_cast<int>(text_sz.first * 0.5),
		static_cast<int>(text_sz.second * 0.5)
	);
	bg_shape = init_bg_shape(bg, text_sz.first, text_sz.second);

	std::cout << "Size: " << text_sz.first << ", "
		<< text_sz.second << std::endl;
}

std::pair<int, int> Text_box::get_bbox_size() const {
	int mv_x = 0, mv_y = 0, sz_x = 0, sz_y = 0;
	Fl_Fontsize old_sz{ fl_size() };
	fl_font(fl_font(), font_size());
	fl_text_extents(label().c_str(), mv_x, mv_y, sz_x, sz_y);
	fl_font(fl_font(), old_sz);
	return std::pair<int, int>(sz_x, sz_y);
}

std::unique_ptr<GL::Shape> Text_box::init_bg_shape(BG_shape bg, int w, int h)
{
	switch(bg) {
	case BG_shape::Box:
		return std::make_unique<BOX::Box>(point(0), w, h, 0.5);
	case BG_shape::Ellipse:
		return std::make_unique<GL::Ellipse>(point(0), w, h);
	default:
		return std::unique_ptr<GL::Shape>();
	}
}

void Text_box::draw_lines() const{
	Text::draw_lines();
	c_mark->draw_lines();
}
