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
           1,
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
            0.25,
            [](void*, void* pw) {
	            (*static_cast<My_window*>(pw)).validate_test2();
            })
    , tgl_test({x_max() / 2, 384},
               64,
               32,
               Graph_lib::Color::dark_green,
               [](void*, void* pw) {
	               (*static_cast<My_window*>(pw)).toggle_test();
               })
    , out({x_max() / 2, 128}, 64, 32, "Result integer")
    , out2({x_max() / 2, 288}, 64, 32, "Result double")
    , out3({x_max() / 2, 448}, 64, 32, "Result toggle")
{
	attach(test);
	attach(out);
	attach(test2);
	attach(out2);
	attach(tgl_test);
	attach(out3);
}

void My_window::validate_test()
{
	out.put(std::to_string(test.value()));
}

void My_window::validate_test2()
{
	out2.put(Validated_double_in_box::format_dbl(test2.value()));
}

void My_window::toggle_test()
{
	tgl_test.toggle();
	out3.put((tgl_test.is_on() ? "ON" : "OFF"));
}
