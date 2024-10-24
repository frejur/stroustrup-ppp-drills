#include "my_win.h"
#include <chrono>
#include <ctime>
#include <sstream>

std::ostream& operator<<(std::ostream& os, Graph_lib::Point pt)
{
	os << "x: " << pt.x << ", y: " << pt.y;
	return os;
}

void My_window::act_prnt(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		std::ostringstream os;
		os << b.position();
		out.put(os.str());
		b.activate();
		active_fn = [row, col, this]() { act_prnt(row, col); };
	} else if (b.is_active()) {
		out.put("");
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_lite(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		Graph_lib::Color bright_c{Graph_lib::Color(fl_rgb_color(250, 225, 175))};
		b.set_fill_color(bright_c);
		b.set_color(Graph_lib::Color::black);
		b.activate();
		active_fn = [row, col, this]() { act_lite(row, col); };
	} else if (b.is_active()) {
		b.reset_fill_color();
		b.reset_color();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_dots(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		Graph_lib::Line_style dots_s{
		    Graph_lib::Line_style(Graph_lib::Line_style::dot, 3)};
		b.set_style(dots_s);
		b.activate();
		active_fn = [row, col, this]() { act_dots(row, col); };
	} else if (b.is_active()) {
		b.reset_style();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_grow(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.activate();
		b.set_font_size(18);
		active_fn = [row, col, this]() { act_grow(row, col); };
	} else if (b.is_active()) {
		b.reset_font_size();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_caps(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.set_label("CAPS");
		b.set_font_size(18);
		b.activate();
		active_fn = [row, col, this]() { act_caps(row, col); };
	} else if (b.is_active()) {
		b.reset_label();
		b.reset_font_size();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_tiny(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.activate();
		b.set_font_size(8);
		active_fn = [row, col, this]() { act_tiny(row, col); };
	} else if (b.is_active()) {
		b.reset_font_size();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_dark(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		Graph_lib::Color dark_c{Graph_lib::Color(fl_rgb_color(40, 40, 55))};
		b.set_fill_color(dark_c);
		b.activate();
		active_fn = [row, col, this]() { act_dark(row, col); };
	} else if (b.is_active()) {
		b.reset_fill_color();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_rght(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	int offs_x = 48;
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}

		b.move(offs_x, 0);
		b.activate();
		active_fn = [row, col, this]() { act_rght(row, col); };
	} else if (b.is_active()) {
		b.move(-offs_x, 0);
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_dash(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		Graph_lib::Line_style dots_s{
		    Graph_lib::Line_style(Graph_lib::Line_style::dash, 2)};
		b.set_style(dots_s);
		b.activate();
		active_fn = [row, col, this]() { act_dash(row, col); };
	} else if (b.is_active()) {
		b.reset_style();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_hide(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.activate();
		b.hide();
		active_fn = [row, col, this]() { act_hide(row, col); };
	} else if (b.is_active()) {
		b.reset_style();
		b.show();
		b.normalize();
		active_fn = 0;
	}
}
void My_window::act_empt(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.set_label("");
		b.activate();
		active_fn = [row, col, this]() { act_empt(row, col); };
	} else if (b.is_active()) {
		b.reset_label();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_wide(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.activate();
		b.set_label("Wiiiiiiiiiiiiiiiide");
		active_fn = [row, col, this]() { act_wide(row, col); };
	} else if (b.is_active()) {
		b.reset_label();
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_down(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	int offs_y = 48;
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}

		b.move(0, offs_y);
		b.activate();
		active_fn = [row, col, this]() { act_down(row, col); };
	} else if (b.is_active()) {
		b.move(0, -offs_y);
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_long(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		b.activate();
		active_fn = [row, col, this]() { act_wide(row, col); };
	} else if (b.is_active()) {
		b.normalize();
		active_fn = 0;
	}
}

void My_window::act_time(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}

		// Get current datetime (copypasta)
		std::chrono::time_point<std::chrono::system_clock> now{
		    std::chrono::system_clock::now()};
		std::time_t time = std::chrono::system_clock::to_time_t(now);

		std::ostringstream os;
		os << std::ctime(&time);
		out.put(os.str());
		b.activate();
		active_fn = [row, col, this]() { act_time(row, col); };
	} else if (b.is_active()) {
		b.normalize();
		out.put("");
		active_fn = 0;
	}
}

void My_window::act_bgrd(int row, int col)
{
	shp_btn::Shape_button& b{btn_from_idx(row, col)};
	if (b.is_normal()) {
		if (active_fn) {
			active_fn();
		}
		Graph_lib::Color new_bg_c{Graph_lib::Color(fl_rgb_color(48, 48, 48))};
		color(new_bg_c.as_int());
		b.activate();
		active_fn = [row, col, this]() { act_bgrd(row, col); };
	} else if (b.is_active()) {
		color(FL_BACKGROUND_COLOR);
		b.normalize();
		active_fn = 0;
	}
}
