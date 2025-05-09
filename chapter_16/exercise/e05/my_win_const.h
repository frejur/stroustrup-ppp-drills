#ifndef MY_WIN_CONST_H
#define MY_WIN_CONST_H
#include "../../lib/Graph.h"
#include <string>

struct Ghost_writer; // Forward declare

namespace Mw_const {

const Ghost_writer& poe();
const Ghost_writer& frank();
const Ghost_writer& doc();

//------------------------------------------------------------------------------

const std::string& image_path();
const std::string& mappings_out_path();
const std::string& mappings_in_path();

//------------------------------------------------------------------------------

const Graph_lib::Color& grid_color();

//------------------------------------------------------------------------------

const std::string& info_welcome();
const std::string& info_press_next_to();
const std::string& info_good_bye();
const std::string& info_click_grid();

//------------------------------------------------------------------------------

const std::string& status_prefix();
const std::string& status_no_connection();
const std::string& status_connected_to();
const std::string& status_lost_connection();
const std::string& status_cleared_mappings();

//------------------------------------------------------------------------------

const Graph_lib::Font& info_font();
const Graph_lib::Font& status_font();

//------------------------------------------------------------------------------

static constexpr int planchette_radius{18};
const Graph_lib::Color& planchette_color();
const Graph_lib::Line_style& planchette_style();
const Graph_lib::Point& goodbye_position();

} // namespace Mw_const
#endif // MY_WIN_CONST_H
