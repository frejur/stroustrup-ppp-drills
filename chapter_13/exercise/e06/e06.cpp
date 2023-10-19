#include "../../lib/Graph.h"
#include "../../lib/GUI.h"
#include "../../lib/Debug_window.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>

/* Exercise 6.
 * Draw the class diagram from 12.6 using rounded boxes and arrows.
 * (Let's throw an ellipse in there too!)
 */

namespace GL = Graph_lib;

void e06()
{
	constexpr bool ENABLE_DEBUG{ true };

	constexpr int win_w{ 960 };
	constexpr int win_h{ 520 };
	constexpr int pad_w{ 150 };
	constexpr int pad_h{ 100 };
	const int win_w_qrt{
		static_cast<int>(std::round((win_w - pad_w * 2) * 0.25))
	};
	const int win_w_8th{
		static_cast<int>(std::round(win_w_qrt * 0.5))
	};
	const int win_w_14th{
		static_cast<int>(std::round(win_w - pad_w * 2) / 14.0)
	};
	const int win_w_16th{
		static_cast<int>(std::round(win_w_8th * 0.5))
	};
	const int win_h_half{
		static_cast<int>(std::round((win_h - pad_h * 2) * 0.5))
	};
	const int win_h_10th{
		static_cast<int>(std::round((win_h - pad_h * 2) * 0.1))
	};
	const GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{ {10, 10}, win_w, win_h, "Classy diagramme",
		ENABLE_DEBUG};

	// TODO: Define a Text_box class

	// Top row -----------------------------------------------------------------
	GL::Text txt_win{ { pad_w + win_w_qrt, pad_h}, "Window"};
	txt_win.set_color(FL_BLACK);
	win.attach(txt_win);

	GL::Text txt_line_style{ {pad_w + win_w_qrt * 2 - win_w_16th, pad_h}, "Line_style" };
	txt_line_style.set_color(FL_BLACK);
	win.attach(txt_line_style);

	GL::Text txt_color{ {pad_w + win_w_qrt * 2 + win_w_8th, pad_h}, "Color" };
	txt_color.set_color(FL_BLACK);
	win.attach(txt_color);

	// Middle row --------------------------------------------------------------
	GL::Text txt_simple_win{ { pad_w + win_w_qrt, pad_h + win_h_half}, "Simple_window"};
	txt_simple_win.set_color(FL_BLACK);
	win.attach(txt_simple_win);

	GL::Text txt_shape{ {pad_w + win_w_qrt * 2, pad_h + win_h_half - win_h_10th}, "Shape" };
	txt_shape.set_color(FL_BLACK);
	win.attach(txt_shape);

	GL::Text txt_point{ {pad_w + win_w_qrt * 2 + win_w_8th + win_w_16th, pad_h + win_h_half}, "Point" };
	txt_point.set_color(FL_BLACK);
	win.attach(txt_point);

	// Bottom row --------------------------------------------------------------
	GL::Text txt_line{ {pad_w + win_w_14th, win_h - pad_h }, "Line" };
	txt_line.set_color(FL_BLACK);
	win.attach(txt_line);

	GL::Text txt_lines{ {pad_w + win_w_14th * 2, win_h - pad_h }, "Lines" };
	txt_lines.set_color(FL_BLACK);
	win.attach(txt_lines);

	GL::Text txt_poly{ {pad_w + win_w_14th * 5, win_h - pad_h }, "Polygon" };
	txt_poly.set_color(FL_BLACK);
	win.attach(txt_poly);

	GL::Text txt_axis{ {pad_w + win_w_14th * 7, win_h - pad_h }, "Axis" };
	txt_axis.set_color(FL_BLACK);
	win.attach(txt_axis);

	GL::Text txt_rect{ {pad_w + win_w_14th * 9, win_h - pad_h }, "Rectangle" };
	txt_rect.set_color(FL_BLACK);
	win.attach(txt_rect);

	GL::Text txt_text{ {pad_w + win_w_14th * 11, win_h - pad_h }, "Text" };
	txt_text.set_color(FL_BLACK);
	win.attach(txt_text);

	GL::Text txt_image{ {pad_w + win_w_14th * 12, win_h - pad_h }, "Image" };
	txt_image.set_color(FL_BLACK);
	win.attach(txt_image);

	win.wait_for_button();
}

int main() {
	try {
		e06();
		return 0;
	}
	catch (std::exception &e) {
		std::cerr<<e.what()<<'\n';
		return 1;
	}
	catch (...) {
		std::cerr<<"Unknown error\n";
		return 2;
	}
}


