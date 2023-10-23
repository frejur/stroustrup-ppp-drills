#include "../../lib/Graph.h"
#include "../../lib/Debug_window.h"
#include "text_box.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "arrow.h"
#include "text_box_helpers.h"

/* Exercise 6.
 * Draw the class diagram from 12.6 using rounded boxes and arrows.
 * (Let's throw some ellipses in there too!)
 */

namespace GL = Graph_lib;
constexpr TBX::Text_box::BG_shape BG_BOX { TBX::Text_box::BG_BOX };
constexpr TBX::Text_box::BG_shape BG_ELLIPSE { TBX::Text_box::BG_ELLIPSE };
const GL::Color COLOR_FILL{ 167 };
const GL::Color COLOR_STROKE{ 57 };
const GL::Line_style BOX_STYLE{ GL::Line_style::solid, 2 };

void add_text_box(Debug_window& win, TBX::Text_box& box)
{
	box.set_fill_color(COLOR_FILL);
	box.set_color(COLOR_STROKE);
	box.set_style(BOX_STYLE);
	win.attach(box);
}

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

	Debug_window win{ {10, 10}, win_w, win_h, "Classy diagramme", ENABLE_DEBUG};

	// Top row -----------------------------------------------------------------
	TBX::Text_box txt_win{
		{ pad_w + win_w_qrt, pad_h}, "Window", BG_ELLIPSE
	};
	add_text_box(win, txt_win);

	TBX::Text_box txt_line_style{
		{pad_w + win_w_qrt * 2 - win_w_16th, pad_h}, "Line_style", BG_ELLIPSE
	};
	add_text_box(win, txt_line_style);

	TBX::Text_box txt_color{
		{pad_w + win_w_qrt * 2 + win_w_8th, pad_h}, "Color", BG_ELLIPSE
	};
	add_text_box(win, txt_color);

	// Middle row --------------------------------------------------------------
	TBX::Text_box txt_simple_win{
		{ pad_w + win_w_qrt, pad_h + win_h_half}, "Simple_window", BG_BOX };
	add_text_box(win, txt_simple_win);

	TBX::Text_box txt_shape{
		{pad_w + win_w_qrt * 2, pad_h + win_h_half - win_h_10th},
		"Shape", BG_ELLIPSE
	};
	add_text_box(win, txt_shape);

	TBX::Text_box txt_point{
		{pad_w + win_w_qrt * 2 + win_w_8th + win_w_16th, pad_h + win_h_half},
		"Point", BG_ELLIPSE };
	add_text_box(win, txt_point);

	// Bottom row --------------------------------------------------------------
	TBX::Text_box txt_line{
		{pad_w + win_w_14th * 2, win_h - pad_h }, "Line", BG_BOX
	};
	add_text_box(win, txt_line);

	TBX::Text_box txt_lines{
		{pad_w + win_w_16th * 4, win_h - pad_h }, "Lines", BG_BOX
	};
	add_text_box(win, txt_lines);

	TBX::Text_box txt_poly{
		{pad_w + win_w_14th * 1 + win_w_16th * 5, win_h - pad_h }, "Polygon", BG_BOX
	};
	add_text_box(win, txt_poly);

	TBX::Text_box txt_axis{
		{pad_w + win_w_14th * 7, win_h - pad_h }, "Axis", BG_BOX
	};
	add_text_box(win, txt_axis);

	TBX::Text_box txt_rect{
		{pad_w + win_w_14th * 6 + win_w_16th * 3, win_h - pad_h }, "Rectangle", BG_BOX
	};
	add_text_box(win, txt_rect);

	TBX::Text_box txt_text{
		{pad_w + win_w_14th * 6 + win_w_16th * 5, win_h - pad_h }, "Text" , BG_BOX
	};
	add_text_box(win, txt_text);

	TBX::Text_box txt_image{
		{pad_w + win_w_14th * 12, win_h - pad_h }, "Image", BG_BOX
	};
	add_text_box(win, txt_image);

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


