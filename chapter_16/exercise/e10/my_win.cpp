#include "my_win.h"

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
    , test2({x_max() / 2, 224},
            64,
            32,
            "Double (-5.5 to 12.25)",
            2.33,
            -5.5,
            12.25,
            [](void*, void* pw) {
	            (*static_cast<My_window*>(pw)).validate_test2();
            })
    , out({x_max() / 2, 128}, 64, 32, "Result integer")
    , out2({x_max() / 2, 288}, 64, 32, "Result double")
{
	attach(test);
	attach(out);
	attach(test2);
	attach(out2);
}

void My_window::validate_test()
{
	out.put(std::to_string(test.get_valid_int()));
}

void My_window::validate_test2()
{
	out2.put(std::to_string(test2.get_valid_double()));
}
