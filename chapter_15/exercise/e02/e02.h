#ifndef E02_H
#define E02_H
#include "../../lib/Window.h"
#include "fct.h"

namespace ch15_e02 {

void e02();

int random_int(int x, int y);
int random_double(double x, double y);

class Btn_win : public Graph_lib::Window
{
public:
	using Graph_lib::Window::Window;
	bool btn_has_been_clicked{false};
};

void repeat_on_click(Btn_win& win,
                     std::function<void(fct::Fct&)> action,
                     fct::Fct& f);

static void cb(void*, void* win_ptr)
{
	auto win = static_cast<Btn_win*>(win_ptr);
	win->btn_has_been_clicked = true;
}

} // namespace ch15_e02

#endif // E02_H
