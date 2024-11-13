#include "my_win.h"
#include <random>

My_window::My_window(Graph_lib::Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , test({x_max() / 2, 64},
           64,
           32,
           "Min 10, max 10",
           0,
           -10,
           10,
           [](void*, void* pw) {
	           (*static_cast<My_window*>(pw)).validate_test();
           })
    , in({x_max() / 2, 128}, 64, 32, "")
{
	attach(test);
	attach(in);
}

void My_window::validate_test()
{
	test.validate();
}
