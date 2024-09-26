#include "e02.h"
#include <random>

int ch15_e02::random_int(int x, int y)
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<> distr(x, y);
	return distr(gen);
}

int ch15_e02::random_double(double x, double y)
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<> distr(x, y);
	return distr(gen);
}

void ch15_e02::repeat_on_click(Btn_win& win,
                               std::function<void(fct::Fct&)> action,
                               fct::Fct& f)
{
	while (win.shown()) {
		while (!win.btn_has_been_clicked) {
			Fl::wait();
		}
		action(f);
		win.btn_has_been_clicked = false;
		Fl::redraw();
	}
}
