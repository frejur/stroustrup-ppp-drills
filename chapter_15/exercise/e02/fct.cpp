#include "fct.h"

fct::Fct::Fct(Fn f,
              double r1,
              double r2,
              Graph_lib::Point xy,
              int count,
              double xscale,
              double yscale)
    : f_(f)
    , r_(valid_range(r1, r2))
    , xy_(xy)
    , count_(valid_count(count))
    , xscale_(xscale)
    , yscale_(yscale)
{
	upd();
}

fct::Fct::Fct(double (*f)(double),
              double r1,
              double r2,
              Graph_lib::Point xy,
              int count,
              double xscale,
              double yscale)
    : Fct{static_cast<Fn>(f), r1, r2, xy, count, xscale, yscale}
{}

//------------------------------------------------------------------------------

void fct::Fct::set_function(Fn f)
{
	f_ = f;
	upd();
}

void fct::Fct::set_function(double (*f)(double))
{
	f_ = static_cast<Fn>(f);
	upd();
}

void fct::Fct::set_range(int start, int end)
{
	r_ = valid_range(start, end);
	upd();
}

void fct::Fct::set_origin(Graph_lib::Point o)
{
	xy_ = o;
	upd();
}

void fct::Fct::set_count(int c)
{
	count_ = valid_count(c);
	upd();
}

void fct::Fct::set_x_scale(double xscale)
{
	xscale_ = xscale;
	upd();
}

void fct::Fct::set_y_scale(double yscale)
{
	yscale_ = yscale;
	upd();
}

//------------------------------------------------------------------------------

fct::Range fct::Fct::valid_range(int start, int end)
{
	if (start - end <= 0) {
		throw std::runtime_error("bad graphing range");
	}
	return {start, end};
}

int fct::Fct::valid_count(int c)
{
	if (c <= 0) {
		throw std::runtime_error("non-positive graphing count");
	}
	return c;
}
//------------------------------------------------------------------------------

// Because the points vector is a private member of Graph_lib::Shape, we
// cannot remove points, we keep all of them, modify their postion if
// needed, and only draw up until the number of points defined in
// the current Fct instance.

void fct::Fct::upd()
{
	double dist = (r_.r2 - r_.r1) / count_;
	double r = r_.r1;

	for (int i = 0; i < count_; ++i) {
		Graph_lib::Point pt{xy_.x + int(r * xscale_),
		                    xy_.y - int(f_(r) * yscale_)};
		if (i > number_of_points() - 1) {
			add(pt);
		} else {
			set_point(i, pt);
		}
		r += dist;
	}
}

void fct::Fct::draw_lines() const
{
	if (count_ == number_of_points()) {
		Graph_lib::Shape::draw_lines();
		return;
	}
	if (count_ > number_of_points()) {
		std::runtime_error("The number of points specified by the Fct "
		                   "object does not match "
		                   "the number of points stored internally");
	}

	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		for (int i = 0; i < count_; ++i) {
			fl_vertex(Shape::point(i).x, Shape::point(i).y);
		}
		fl_end_complex_polygon();
		fl_color(color().as_int()); // reset color
	}

	if (color().visibility() && 1 < count_) // draw sole pixel?
		for (unsigned int i = 1; i < count_; ++i)
			fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
}
