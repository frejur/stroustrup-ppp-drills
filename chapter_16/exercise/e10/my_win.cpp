#include "my_win.h"
#include <random>

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , test({x_max() / 2, 64},
           64,
           32,
           "Integer (-10 to 10)",
           0,
           -10,
           10,
           [](void*, void* pw) {
	           (*static_cast<My_window*>(pw)).validate_test();
           })
    , out({x_max() / 2, 128}, 64, 32, "Result")
{
	attach(test);
	attach(out);
}

void My_window::validate_test()
{
	test.validate();
	out.put(std::to_string(test.get_valid_int()));
}
