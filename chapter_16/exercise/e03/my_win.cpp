#include "my_win.h"
#include <random>

namespace {
constexpr int button_width{80};
constexpr int button_height{32};
constexpr int button_font_size{22};

const std::string& image_file_path()
{
	static const std::string p{"honeycomb_80_32.jpg"};
	return p;
}
const std::vector<std::string>& labels()
{
	static const std::vector<std::string> v{"Poke?",
	                                        "Ouch!",
	                                        "Stop it!",
	                                        "Don't.",
	                                        "Please.",
	                                        "Cut it.",
	                                        "Hey!",
	                                        "Bzzz!"};
	return v;
}

const Graph_lib::Color& default_color()
{
	static const Graph_lib::Color c{Graph_lib::Color::black};
	return c;
}

inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

} // namespace

char My_window::num_clk = 0;

//------------------------------------------------------------------------------

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , btn_img({164, 64},
              button_width,
              button_height,
              labels().front(),
              cb,
              image_file_path())
{
	size_range(w, h, w, h); // Lock window size
	Graph_lib::Color new_bg_c{Graph_lib::Color(fl_rgb_color(48, 48, 48))};
	color(new_bg_c.as_int());
	attach(btn_img);
	btn_img.set_font_size(button_font_size);
	btn_img.set_color(default_color());
}

void My_window::scurry()
{
	int target_x = rand_int(0, x_max() - button_width);
	int target_y = rand_int(0, y_max() - button_height);
	btn_img.move(target_x - btn_img.position().x,
	             target_y - btn_img.position().y);
	btn_img.set_label(labels()[number_of_clicks() % labels().size()]);
}
