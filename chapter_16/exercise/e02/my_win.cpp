#include "my_win.h"

namespace {
constexpr int button_width{64};
constexpr int button_height{64};
constexpr int button_horizontal_padding{4};
constexpr int button_vertical_padding{4};
constexpr int out_box_width{144};
constexpr int out_box_height{32};
constexpr int window_top_margin{32};

// A less verbose version of Graph_lib::reference_to, to save horizontal space
My_window& Win_ref(void* pw)
{
	return *static_cast<My_window*>(pw);
}

} // namespace

//------------------------------------------------------------------------------

std::vector<std::string> My_window::lb_v = {
    // clang-format off
    "Print", "Light", "Dots", "Grow",// Row 0
    "Caps", "Tiny", "Dark", "Right", // Row 1
    "Dash", "Hide", "Empty", "Wide", // Row 2
    "Down", "Long", "Time", "BG"     // Row 3
    // clang-format on
};

std::vector<Graph_lib::Callback> My_window::cb_v = {
    // Row 0
    [](void*, void* pw) { Win_ref(pw).act_prnt(0, 0); },
    [](void*, void* pw) { Win_ref(pw).act_lite(0, 1); },
    [](void*, void* pw) { Win_ref(pw).act_dots(0, 2); },
    [](void*, void* pw) { Win_ref(pw).act_grow(0, 3); },
    //Row 1
    [](void*, void* pw) { Win_ref(pw).act_caps(1, 0); },
    [](void*, void* pw) { Win_ref(pw).act_tiny(1, 1); },
    [](void*, void* pw) { Win_ref(pw).act_dark(1, 2); },
    [](void*, void* pw) { Win_ref(pw).act_rght(1, 3); },
    // Row 2
    [](void*, void* pw) { Win_ref(pw).act_dash(2, 0); },
    [](void*, void* pw) { Win_ref(pw).act_hide(2, 1); },
    [](void*, void* pw) { Win_ref(pw).act_empt(2, 2); },
    [](void*, void* pw) { Win_ref(pw).act_wide(2, 3); },
    // Row 3
    [](void*, void* pw) { Win_ref(pw).act_down(3, 0); },
    [](void*, void* pw) { Win_ref(pw).act_long(3, 1); },
    [](void*, void* pw) { Win_ref(pw).act_time(3, 2); },
    [](void*, void* pw) { Win_ref(pw).act_bgrd(3, 3); }};

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , active_fn(0)
    , out(xy, out_box_width, out_box_height, "")

{
	size_range(w, h, w, h); // Lock window size

	if (lb_v.size() != rows * cols) {
		std::runtime_error(
		    "The number of labels does not match the number of buttons");
	}
	if (cb_v.size() != rows * cols) {
		std::runtime_error(
		    "The number of callbacks does not match the number of buttons");
	}

	int offs_x = button_width + button_horizontal_padding;
	int offs_y = button_height + button_vertical_padding;
	int grid_w = button_width + offs_x * (cols - 1);
	int grid_h = button_height + offs_y * (rows - 1);
	int mid_x = static_cast<int>(std::round(w * 0.5));
	int start_x = mid_x - static_cast<int>(std::round(grid_w * 0.5));
	int start_y = window_top_margin
	              + static_cast<int>(
	                  std::round((h - window_top_margin) * 0.5 - grid_h * 0.5));

	int count = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int x = start_x + offs_x * c;
			int y = start_y + offs_y * r;
			int offs_x = 0;
			int offs_y = 0;

			// If the size of the button changes, this needs to be defined
			// upon initialization
			if (r == 0 && c == 3) {
				// Grow
				btn_grid.push_back(new shp_btn::Shape_button{{x, y},
				                                             button_width,
				                                             button_height,
				                                             button_width + 32,
				                                             button_height + 32,
				                                             lb_v[count],
				                                             cb_v[count]});
				offs_y = -32;
			} else if (r == 1 && c == 1) {
				// Tiny (Shrink)
				btn_grid.push_back(new shp_btn::Shape_button{{x, y},
				                                             button_width,
				                                             button_height,
				                                             28,
				                                             28,
				                                             lb_v[count],
				                                             cb_v[count]});
				offs_x = (button_width - 28) / 2;
				offs_y = (button_height - 28) / 2;
			} else if (r == 2 && c == 3) {
				// Wide (Strech horizontally)
				btn_grid.push_back(new shp_btn::Shape_button{{x, y},
				                                             button_width,
				                                             button_height,
				                                             button_width * 3,
				                                             button_height,
				                                             lb_v[count],
				                                             cb_v[count]});
			} else if (r == 3 && c == 1) {
				// Long (Stretch vertically)
				btn_grid.push_back(new shp_btn::Shape_button{{x, y},
				                                             button_width,
				                                             button_height,
				                                             button_width,
				                                             button_height * 2,
				                                             lb_v[count],
				                                             cb_v[count]});
			} else {
				// No transformation
				btn_grid.push_back(new shp_btn::Shape_button{{x, y},
				                                             button_width,
				                                             button_height,
				                                             lb_v[count],
				                                             cb_v[count]});
			}
			attach(btn_grid[btn_grid.size() - 1]);
			if (offs_x != 0 || offs_y != 0) {
				btn_grid[btn_grid.size() - 1].offset_active_position(offs_x,
				                                                     offs_y);
			}
			if ((count + r) % 2 != 0) {
				Graph_lib::Color odd_fill{
				    Graph_lib::Color(fl_rgb_color(85, 139, 130))};
				btn_grid[btn_grid.size() - 1].set_fill_color(odd_fill);
				btn_grid[btn_grid.size() - 1].set_current_fill_color_as_default();
			}
			++count;
		}
	}

	// Attach and position Out_box
	attach(out);
	out.move(mid_x - static_cast<int>(std::round(out_box_width * 0.5)),
	         window_top_margin);
}
