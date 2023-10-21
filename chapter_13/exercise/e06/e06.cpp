#include "../../lib/Graph.h"
#include "../../lib/Debug_window.h"
#include "text_box.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>

/* Exercise 6.
 * Draw the class diagram from 12.6 using rounded boxes and arrows.
 * (Let's throw an ellipse in there too!)
 */

namespace GL = Graph_lib;
constexpr TBX::Text_box::BG_shape BG_BOX { TBX::Text_box::BG_BOX };
constexpr TBX::Text_box::BG_shape BG_ELLIPSE { TBX::Text_box::BG_ELLIPSE };

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
	Debug_window win{ {10, 10}, win_w, win_h, "Classy diagramme",
		ENABLE_DEBUG};

//	fl_color(FL_BLACK);

	// Top row -----------------------------------------------------------------
	TBX::Text_box txt_win{
		{ pad_w + win_w_qrt, pad_h}, "Window", BG_ELLIPSE
	};
	win.attach(txt_win);

	TBX::Text_box txt_line_style{
		{pad_w + win_w_qrt * 2 - win_w_16th, pad_h}, "Line_style", BG_BOX
	};
	txt_line_style.set_fill_color(FL_YELLOW);
	std::cout << "Fill color: " << txt_line_style.fill_color().as_int() << std::endl;
	std::cout << "Fill color visibility: " << std::to_string(txt_line_style.fill_color().visibility()) << std::endl;
	win.attach(txt_line_style);

	GL::Rectangle test{ {0}, 10, 10};
	test.set_fill_color(FL_YELLOW);
	std::cout << "Fill color: " << test.fill_color().as_int() << std::endl;
	std::cout << "Fill color visibility: " << std::to_string(test.fill_color().visibility()) << std::endl;
	win.attach(test);

	TBX::Text_box txt_color{
		{pad_w + win_w_qrt * 2 + win_w_8th, pad_h}, "Color", BG_ELLIPSE
	};
	win.attach(txt_color);

	// Middle row --------------------------------------------------------------
	TBX::Text_box txt_simple_win{
		{ pad_w + win_w_qrt, pad_h + win_h_half}, "Simple_window", BG_BOX };
	win.attach(txt_simple_win);

	TBX::Text_box txt_shape{
		{pad_w + win_w_qrt * 2, pad_h + win_h_half - win_h_10th},
		"Shape", BG_ELLIPSE
	};
	win.attach(txt_shape);

	TBX::Text_box txt_point{
		{pad_w + win_w_qrt * 2 + win_w_8th + win_w_16th, pad_h + win_h_half},
		"Point", BG_BOX };
	win.attach(txt_point);

	// Bottom row --------------------------------------------------------------
	TBX::Text_box txt_line{
		{pad_w + win_w_14th, win_h - pad_h }, "Line", BG_BOX
	};
	win.attach(txt_line);

	TBX::Text_box txt_lines{
		{pad_w + win_w_14th * 2, win_h - pad_h }, "Lines", BG_BOX
	};
	win.attach(txt_lines);

	TBX::Text_box txt_poly{
		{pad_w + win_w_14th * 5, win_h - pad_h }, "Polygon", BG_BOX
	};
	win.attach(txt_poly);

	TBX::Text_box txt_axis{
		{pad_w + win_w_14th * 7, win_h - pad_h }, "Axis", BG_BOX
	};
	win.attach(txt_axis);

	TBX::Text_box txt_rect{
		{pad_w + win_w_14th * 9, win_h - pad_h }, "Rectangle", BG_BOX
	};
	win.attach(txt_rect);

	TBX::Text_box txt_text{
		{pad_w + win_w_14th * 11, win_h - pad_h }, "Text" , BG_BOX
	};
	win.attach(txt_text);

	TBX::Text_box txt_image{
		{pad_w + win_w_14th * 12, win_h - pad_h }, "Image", BG_BOX
	};
	win.attach(txt_image);

	win.wait_for_button();
}

int main() {
	try {
		e06();
		return 0;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
}


