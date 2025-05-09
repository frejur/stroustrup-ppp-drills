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
	static const std::string s{"Click on a node to display its address."};
	return s;
}

//------------------------------------------------------------------------------

void e11_to_14()
{
	using namespace ch14_e11;
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{864};
	constexpr int win_h{480};
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Noodling around",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);
	
	Graph_lib::Text info{{64, 32}, info_click()};
	win.attach(info);

	Circle_binary_tree cbt{{c.x, 50}, 5, 15};
	cbt.set_line_type(Line_type::Down_arrow);
	win.attach(cbt);

	Box_binary_tree bbt{{c.x, 290}, 3, 20};
	bbt.set_line_type(Line_type::Up_arrow);
	win.attach(bbt);

	while (win.shown()) {
		if (win.click_has_been_registered()) {
			int pt = cbt.find_node_at_point(win.click_position());
			if (pt > -1) {
				std::string a = cbt.index_to_address(pt);
				std::string lab = (pt == 0) ? "root" : a;
				cbt.set_label(cbt.index_to_address(pt), lab);
			}

			pt = bbt.find_node_at_point(win.click_position());
			if (pt > -1) {
				std::string a = bbt.index_to_address(pt);
				std::string lab = (pt == 0) ? "root" : a;
				bbt.set_label(bbt.index_to_address(pt), lab);
			}
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
