#include "my_win.h"
#include "../share/ch16_helpers.h"
#include "my_win_const.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>

void In_box_control::attach(Graph_lib::Window& win)
{
	pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window

	// Trigger callback upon edit
	pw->when(FL_WHEN_CHANGED);
	own = &win;
}

string In_box_control::get_string()
{
	Fl_Input* p = static_cast<Fl_Input*>(pw);
	return string{p->value()};
}

void In_box_control::clear()
{
	(*static_cast<Fl_Input*>(pw)).value("");
}

//------------------------------------------------------------------------------

My_button::My_button(Graph_lib::Point top_left,
                     const string& label,
                     Graph_lib::Callback callback_fn,
                     Graph_lib::Color bg_color)
    : shp_btn::Shape_button(top_left,
                            My_button::width,
                            My_button::height,
                            label,
                            callback_fn,
                            bg_color)
{
	set_font_size(My_button::font_size);
}

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Graph_lib::Window::Window(xy, w, h, title)
    , should_reload(false)
    , st(Window_state::None)
    , gdbye_xy(Mw_const::goodbye_position())
    , txt_info({0, top_m / 2 + info_fsz / 2}, "")
    , txt_status({status_l_pad, y_max() - btm_m / 2 + status_fsz * 2},
                 Mw_const::status_prefix())
    , bg({0, 0}, Mw_const::image_path())
    , speak_btn({0, 0}, "Speak", cb_speak)
    , speak_menu({0, 0},
                 My_button::width,
                 My_button::height + btn_pad,
                 Graph_lib::Menu::Kind::vertical,
                 "")
    , next_btn({0, 0}, "Next", cb_next)
    , quit_btn({0, 0}, "Quit", cb_quit)
    , map_btn({0, 0}, "Remap", cb_map)
    , map_menu({0, 0},
               My_button::width + btn_pad,
               My_button::height,
               Graph_lib::Menu::Kind::horizontal,
               "Menu")
    , planch({128, 128}, Mw_const::planchette_radius)
{
	// BG and text
	attach(bg);
	attach(txt_info);
	attach(txt_status);
	txt_info.set_font(Mw_const::info_font());
	txt_info.set_font_size(info_fsz);
	txt_status.set_font(Mw_const::status_font());
	txt_status.set_font_size(status_fsz);

	// Planchette
	attach(planch);
	planch.set_color(Mw_const::planchette_color());
	planch.set_style(Mw_const::planchette_style());

	create_speak_buttons();
	create_mapping_screen();

	prep_for_normal();
}

//------------------------------------------------------------------------------

void My_window::upd_txt_info(const string& new_text)
{
	txt_info.set_label(new_text);
	int w = ch16_hlp::calc_lb_w(new_text, txt_info.font(), txt_info.font_size());
	int x = static_cast<int>(std::round(x_max() * 0.5 - w * 0.5));
	txt_info.move(x - txt_info.point(0).x, 0);
}

void My_window::upd_txt_status(const string& new_text)
{
	txt_status.set_label(Mw_const::status_prefix() + new_text);
}

//------------------------------------------------------------------------------

void My_window::mod_all_map_grid_elem(Grid_element_action a)
{
	const int n = valid_map_num_grid_elem();
	for (int i = 0; i < n; ++i) {
		mod_map_grid_elem(i, a, true);
	}
}

void My_window::mod_map_grid_elem(int idx,
                                  Grid_element_action a,
                                  bool skip_check)
{
	if (!skip_check) {
		idx = valid_map_elem_idx(idx);
	}
	using Gr_a = Grid_element_action;
	switch (a) {
	case Gr_a::Hide:
		map_grid_inp[idx].hide();
		map_grid_rct[idx].set_color(
		    Graph_lib::Color(Graph_lib::Color::black,
		                     Graph_lib::Color::invisible));
		break;
	case Gr_a::Show:
		map_grid_inp[idx].show();
		map_grid_rct[idx].set_color(Mw_const::grid_color());
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------

int My_window::num_unmap() const
{
	int n = 0;
	for (int i = 0; i < map_chars.size(); ++i) {
		n += (map_chars[i].is_mapped()) ? 0 : 1;
	}
	return n;
}

void My_window::map_ch(char c, Graph_lib::Point new_xy)
{
	for (int i = 0; i < map_chars.size(); ++i) {
		Map_char& m = map_chars[i];
		if (m.label().front() != c) {
			continue;
		}
		m.mark_as_mapped();
		m.set_mapped_position(new_xy);
		return;
	}

	throw std::runtime_error(
	    "Char " + std::string{c}
	    + " was not found in the list of characters to be mapped");
}

void My_window::mod_all_map_chars(Char_action a)
{
	const int n = valid_map_num_chars();
	for (int i = 0; i < n; ++i) {
		switch (a) {
		case Char_action::Mark_mapped:
			map_chars[i].mark_as_mapped();
			break;
		case Char_action::Mark_unmapped:
			map_chars[i].mark_as_unmapped();
			break;
		case Char_action::Show:
			map_chars[i].show();
			break;
		case Char_action::Hide:
			map_chars[i].hide();
			break;
		}
	}
}
//------------------------------------------------------------------------------

int My_window::valid_map_char_idx(int idx)
{
	if (idx < 0 || idx > map_num_chars) {
		std::runtime_error("Invalid char index");
	}
	return idx;
}

int My_window::valid_map_elem_idx(int idx)
{
	if (idx < 0 || idx > valid_map_num_grid_elem()) {
		std::runtime_error("Invalid char index");
	}
	return idx;
}

int My_window::valid_map_num_chars() const
{
	if (map_chars.size() != map_num_chars) {
		throw std::runtime_error(
		    "Invalid number of mapping characters, expected: "
		    + std::to_string(map_num_chars)
		    + ", got: " + std::to_string(map_chars.size()));
	}
	return map_num_chars;
}

int My_window::valid_map_num_grid_elem() const
{
	if (map_grid_inp.size() == 0 || map_grid_rct.size() != map_grid_inp.size()) {
		throw std::runtime_error(
		    "The mapping elements(Inputs, Rectangles) were not properly "
		    "intialized, the size of both containers should be: "
		    + ((map_grid_rct.size() == 0)
		           ? "gr than zero"
		           : std::to_string(map_grid_inp.size())));
	}
	return map_grid_inp.size();
}
//------------------------------------------------------------------------------

void My_window::read_file_into_stream(const string& file_path)
{
	std::ifstream ifs(file_path);

	if (!ifs) {
		throw std::runtime_error("Couldn not open file '" + file_path
		                         + "' for input");
	}

	std::string txt;
	char c;
	while (ifs.get(c)) {
		txt += c;
	}

	if (!ch_stream) {
		ch_stream.clear(std::ios_base::goodbit);
	}
	ch_stream.str(txt);
}

//------------------------------------------------------------------------------

void My_window::prep_for_normal()
{
	if (st == My_window::Window_state::Normal) {
		return;
	}

	if (st == My_window::Window_state::None) {
		load_map(Mw_const::mappings_in_path()); // Load default mappings
	} else if (should_reload) {
		mod_all_map_chars(Char_action::Mark_unmapped);
		load_map(Mw_const::mappings_out_path()); // Load remappings
	}

	mod_all_map_grid_elem(Grid_element_action::Hide);
	mod_all_map_chars(Char_action::Hide);
	map_menu.hide();
	quit_btn.hide();
	next_btn.hide();
	speak_menu.hide();
	speak_btn.show();
	map_btn.show();
	upd_txt_info(Mw_const::info_welcome());
	upd_txt_status(Mw_const::status_no_connection());
	planch.move(gdbye_xy.x - planch.center().x, gdbye_xy.y - planch.center().y);
	st = Window_state::Normal;
}

void My_window::prep_for_ouija(const Ghost_writer& writer)
{
	if (st != My_window::Window_state::Normal) {
		return;
	}
	read_file_into_stream(writer.file_path);
	speak_menu.hide();
	map_btn.hide();
	next_btn.show();
	quit_btn.show();
	quit_btn.move(0, map_btn.position().y - quit_btn.position().y);
	upd_txt_info(Mw_const::info_press_next_to() + "\"" + writer.aka + "\".");
	upd_txt_status(Mw_const::status_connected_to() + writer.name);
	st = Window_state::Ouija;
}

void My_window::prep_for_remap()
{
	if (st != My_window::Window_state::Normal) {
		return;
	}
	speak_btn.hide();
	speak_menu.hide();
	map_btn.hide();
	mod_all_map_grid_elem(Grid_element_action::Show);
	mod_all_map_chars(Char_action::Show);
	map_menu.show();
	upd_txt_info(Mw_const::info_click_grid());
	upd_txt_status(Mw_const::status_prefix() + "Waiting for user");
	st = Window_state::Remapping;
}
