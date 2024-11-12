#include "my_win.h"
#include "my_win_const.h"
#include <sstream>

namespace {

char to_upper_if_lower(char c)
{
	if (c >= 'a' && c <= 'z') {
		return c + ('A' - 'a');
	}
	return c;
}

} // namespace

// A less verbose version of Graph_lib::reference_to, to save horizontal space
My_window& Wref(void* pw)
{
	return *static_cast<My_window*>(pw);
}

//------------------------------------------------------------------------------
// clang-format off
void My_window::cb_speak(void*, void* pw) { Wref(pw).show_speak_to_menu(); };
void My_window::cb_next(void*, void* pw) { Wref(pw).move_planchette(); };
void My_window::cb_quit(void*, void* pw) { Wref(pw).abort_seance(); };
void My_window::cb_map(void*, void* pw) { Wref(pw).show_remapping_screen(); };
void My_window::cb_map_clear(void*, void* pw) { Wref(pw).clear_remappings(); };
void My_window::cb_map_abort(void*, void* pw) { Wref(pw).abort_remapping(); };
void My_window::cb_map_save(void*, void* pw) { Wref(pw).save_remappings(); };
// clang-format on
//------------------------------------------------------------------------------

void My_window::get_and_remap_char()
{
	if (st != Window_state::Remapping) {
		return;
	}
	std::ostringstream os;
	os << Mw_const::status_prefix();
	for (int i = 0; i < map_grid_inp.size(); ++i) {
		std::string val = map_grid_inp[i].get_string();
		if (val.size() == 0) {
			continue;
		}
		char c = to_upper_if_lower(val.front());
		if (is_valid_ch(c)) {
			int x = map_grid_inp[i].loc.x + unit_sz / 2;
			int y = map_grid_inp[i].loc.y + unit_sz / 2;
			map_ch(c, {x, y});
			os << "Mapped '" << c << " to (" << x << ", " << y << "), ";
			has_remapped_chars = true; // Will set should_relad flag upon save
		} else {
			os << "Cannot map that character. ";
		}
		os << num_unmap() << " remaining.";
		map_grid_inp[i].clear();
		break;
	}
	txt_status.set_label(os.str());
	redraw();
}

//------------------------------------------------------------------------------

void My_window::show_speak_to_menu()
{
	speak_menu.show();
	speak_btn.hide();
}

//------------------------------------------------------------------------------
// clang-format off
void My_window::speak_to_poe() { prep_for_ouija(Mw_const::poe()); };
void My_window::speak_to_frank() { prep_for_ouija(Mw_const::frank()); };
void My_window::speak_to_doc() { prep_for_ouija(Mw_const::doc()); };
// clang-format on
//------------------------------------------------------------------------------

void My_window::move_planchette()
{
	if (st != My_window::Window_state::Ouija) {
		return;
	}

	char c{};
	while (ch_stream >> c) {
		c = to_upper_if_lower(c);
		if (is_valid_ch(c)) {
			break;
		}
	}

	if (ch_stream) {
		for (int i = 0; i < map_chars.size(); ++i) {
			Map_char& m = map_chars[i];
			if (m.label().front() != c) {
				continue;
			}
			planch.move(m.mapped_position().x - planch.center().x,
			            m.mapped_position().y - planch.center().y);
			redraw();
			return;
		}
	}

	// The end, move planchette to Good Bye, hide 'Next' button
	upd_txt_info(Mw_const::info_good_bye());
	upd_txt_status(Mw_const::status_lost_connection());
	planch.move(gdbye_xy.x - planch.center().x, gdbye_xy.y - planch.center().y);
	next_btn.hide();
	// redraw();
}

//------------------------------------------------------------------------------

void My_window::abort_seance()
{
	if (st != My_window::Window_state::Ouija) {
		return;
	}
	quit_btn.move(0, next_btn.position().y - quit_btn.position().y);
	prep_for_normal();
}

//------------------------------------------------------------------------------

void My_window::show_remapping_screen()
{
	prep_for_remap();
}
void My_window::abort_remapping()
{
	prep_for_normal();
}
void My_window::clear_remappings()
{
	if (st != My_window::Window_state::Remapping) {
		return;
	}
	mod_all_map_chars(Char_action::Mark_unmapped);
	upd_txt_status(Mw_const::status_cleared_mappings());
	redraw();
}
void My_window::save_remappings()
{
	if (has_remapped_chars) {
		should_reload = true; // Will trigger the loading of remappings from file
	}
	save_map(Mw_const::mappings_out_path());
	prep_for_normal();
}

//------------------------------------------------------------------------------
