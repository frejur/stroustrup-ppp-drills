#include "my_win_const.h"
#include "my_win.h"

const Ghost_writer& Mw_const::poe()
{
	static const Ghost_writer gw{"Poe", "Edgar", "txt_e05/poe.txt"};
	return gw;
}

const Ghost_writer& Mw_const::frank()
{
	static const Ghost_writer gw{"Frank", "Ol' Blue Eyes", "txt_e05/frank.txt"};
	return gw;
}

const Ghost_writer& Mw_const::doc()
{
	static const Ghost_writer gw{"Doc", "Emmett", "txt_e05/doc.txt"};
	return gw;
}
//------------------------------------------------------------------------------

const std::string& Mw_const::image_path()
{
	static const std::string s{"img_e05/ouija.png"};
	return s;
}

const std::string& Mw_const::mappings_out_path()
{
	static const std::string s{"txt_e05/remappings.txt"};
	return s;
}

const std::string& Mw_const::mappings_in_path()
{
	static const std::string s{"txt_e05/mappings_backup.txt"};
	return s;
}
//------------------------------------------------------------------------------

const Graph_lib::Color& Mw_const::grid_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}
//------------------------------------------------------------------------------

const std::string& Mw_const::info_welcome()
{
	static const std::string s{"Welcome, who do you want to speak to?"};
	return s;
}

const std::string& Mw_const::info_press_next_to()
{
	static const std::string s{"Keep pressing 'Next' to speak to "};
	return s;
}

const std::string& Mw_const::info_good_bye()
{
	static const std::string s{"We hope you enjoyed this otherworldly wisdom."};
	return s;
}

const std::string& Mw_const::info_click_grid()
{
	static const std::string s{
	    "Click on the grid below then type a character."};
	return s;
}
//------------------------------------------------------------------------------

const std::string& Mw_const::status_prefix()
{
	static const std::string s{"Status: "};
	return s;
}

const std::string& Mw_const::status_no_connection()
{
	static const std::string s{"Not connected."};
	return s;
}

const std::string& Mw_const::status_connected_to()
{
	static const std::string s{"Connected to "};
	return s;
}

const std::string& Mw_const::status_lost_connection()
{
	static const std::string s{"Connection lost."};
	return s;
}

const std::string& Mw_const::status_cleared_mappings()
{
	static const std::string s{"All mappings were cleared."};
	return s;
}
//------------------------------------------------------------------------------

const Graph_lib::Font& Mw_const::info_font()
{
	const static Graph_lib::Font f{Graph_lib::Font::helvetica_bold};
	return f;
}

const Graph_lib::Font& Mw_const::status_font()
{
	const static Graph_lib::Font f{Graph_lib::Font::helvetica_bold};
	return f;
}

//------------------------------------------------------------------------------

const Graph_lib::Color& Mw_const::planchette_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}

const Graph_lib::Line_style& Mw_const::planchette_style()
{
	static const Graph_lib::Line_style s{
	    Graph_lib::Line_style(Graph_lib::Line_style::solid, 5)};
	return s;
}

//------------------------------------------------------------------------------

const Graph_lib::Point& Mw_const::goodbye_position()
{
	static const Graph_lib::Point xy{235, 280};
	return xy;
}

// Window constants ------------------------------------------------------------

const int My_window::left_m = 72;
const int My_window::right_m = 72;
const int My_window::top_m = 32;
const int My_window::btm_m = 96;
const int My_window::btn_pad = 2;
const int My_window::unit_sz = 4;
const int My_window::info_fsz = 16;
const int My_window::status_fsz = 12;
const int My_window::status_l_pad = 32;
const int My_window::speak_r_pad = 16;
const int My_window::speak_top_pad = 16;
const int My_window::map_btn_r_pad = 16;
const int My_window::map_btn_btm_pad = 16;
