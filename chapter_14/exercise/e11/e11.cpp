#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "binary_tree.h"

// Chapter 14, exercise 11 to 14.
//
// Binary trees
//
// - Ex. 11: Define class 'Binary_tree', derived from 'Shape', that draws
//           a (perfect) binary tree using small circles connected by lines.
//           The parameter 'levels' controls the number of nodes.
// - Ex. 12: Derive a class from 'Binary_tree' that uses an overriden virtual
//           function for drawing different node / leaf shapes(e.g. triangles).
// - Ex. 13: Add parameters to control the appearance of the lines other than
//           color, thickness and style (e.g. Up or downward pointing arrows)
// - Ex. 14: Add a method to label nodes / leaves, use a sequence of the chars
//           'l' and 'r' to specify which leaf to label (e.g. 'llrl' means
//           left-right-left from the root, and the initial 'l' or 'r' always
//           means the root)
//-----------------------------------------------------------------------------

const std::string& info_click()
{
	static const std::string s{"Click on a node / leaf."};
	return s;
}

//------------------------------------------------------------------------------

void e11_to_14()
{
	using namespace ch14_e11;
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Baby's got mono",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);
	
	Graph_lib::Text info{{64, 32}, info_click()};
	win.attach(info);

	Binary_tree bt{{c.x, 50}, 5};
	win.attach(bt);

	while (win.shown()) {
		if (win.click_has_been_registered()) {
			// TODO: Highlight path of leaf, display address.
			bt.move_sub_tree(1, -10, 10);
		}
		win.wait_for_click();
	}
}


int main() {
	try {
		e11_to_14();
		return 0;
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
