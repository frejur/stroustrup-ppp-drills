#include "my_win.h"
#include "my_win_const.h"

void My_window::create_speak_buttons()
{
	attach(speak_btn);

	speak_menu.attach(
	    new My_button{{0, 0}, Mw_const::poe().name, [](void*, void* pw) {
		                  (*static_cast<My_window*>(pw)).speak_to_poe();
	                  }});
	speak_menu.attach(
	    new My_button{{0, 0}, Mw_const::frank().name, [](void*, void* pw) {
		                  (*static_cast<My_window*>(pw)).speak_to_frank();
	                  }});
	speak_menu.attach(
	    new My_button{{0, 0}, Mw_const::doc().name, [](void*, void* pw) {
		                  (*static_cast<My_window*>(pw)).speak_to_doc();
	                  }});
	attach(speak_menu);

	attach(next_btn);
	attach(quit_btn);
	int x = x_max() - speak_r_pad - My_button::width;
	int y = speak_top_pad;
	speak_btn.move(x, y);
	speak_menu.move(x, y);
	next_btn.move(x, y);
	quit_btn.move(x, y);
};

void My_window::create_mapping_screen()

{
	// Grid
	const int grid_w = x_max() - left_m - right_m;
	const int grid_h = y_max() - top_m - btm_m;
	const int num_x = static_cast<int>(grid_w / unit_sz);
	const int num_y = static_cast<int>(grid_h / unit_sz);
	for (int r = 0; r < num_y; ++r) {
		for (int c = 0; c < num_x; ++c) {
			int x = left_m + c * unit_sz;
			int y = top_m + r * unit_sz;
			map_grid_inp.push_back(new In_box_control{
			    {x, y}, unit_sz, unit_sz, "", [](void*, void* pw) {
				    (*static_cast<My_window*>(pw)).get_and_remap_char();
			    }});
			attach(map_grid_inp[map_grid_inp.size() - 1]);

			map_grid_rct.push_back(
			    (new Graph_lib::Rectangle{{x, y}, unit_sz, unit_sz}));
			attach(map_grid_rct[map_grid_rct.size() - 1]);
		}
	}

	// Characters A - Z
	const int chars_x = 32;
	const int chars_y = y_max() - static_cast<int>(btm_m / 2);
	const int char_w = 12;
	for (char c = 'A'; c <= 'Z'; ++c) {
		map_chars.push_back(
		    new Map_char{{chars_x + (c - 'A') * char_w, chars_y}, c});
		attach(map_chars[map_chars.size() - 1]);
	}

	// Digits
	const int dig_x = chars_x + ((static_cast<int>('Z' - 'A') + 2) * char_w);
	const int dig_y = chars_y;
	const int dig_w = 8;
	for (char d = '0'; d <= '9'; ++d) {
		map_chars.push_back(new Map_char{{dig_x + (d - '0') * dig_w, dig_y}, d});
		attach(map_chars[map_chars.size() - 1]);
	}

	// Remap button
	attach(map_btn);
	map_btn.move(x_max() - map_btn_r_pad - My_button::width,
	             y_max() - map_btn_btm_pad - My_button::height);

	// Menu Buttons
	map_menu.attach(new My_button{{0, 0}, "Abort", cb_map_abort});
	map_menu.attach(new My_button{{0, 0}, "Clear", cb_map_clear});
	map_menu.attach(new My_button{{0, 0}, "Save", cb_map_save});
	attach(map_menu);
	const int btn_x = dig_x + 10 * dig_w - My_button::width * 3;
	const int btn_y = dig_y + unit_sz + btn_pad;
	map_menu.move(btn_x, btn_y);
}
