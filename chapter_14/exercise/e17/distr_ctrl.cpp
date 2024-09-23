#include "distr_ctrl.h"

void ch14_e17::Shape_controller::show()
{
	Graph_lib::Color c = s.color();
	if (!c.visibility()) {
		c.set_visibility(Graph_lib::Color::Transparency::visible);
		s.set_color(c);
	}
	Graph_lib::Color fc = s.fill_color();
	if (!fc.visibility()) {
		fc.set_visibility(Graph_lib::Color::Transparency::visible);
		s.set_fill_color(fc);
	}
}

void ch14_e17::Shape_controller::hide()
{
	Graph_lib::Color c = s.color();
	if (c.visibility()) {
		c.set_visibility(Graph_lib::Color::Transparency::invisible);
		s.set_color(c);
	}
	Graph_lib::Color fc = s.fill_color();
	if (fc.visibility()) {
		fc.set_visibility(Graph_lib::Color::Transparency::invisible);
		s.set_fill_color(fc);
	}
}

//------------------------------------------------------------------------------

ch14_e17::Distributor_controller::Distributor_controller(Shape_distributor& dist)
    : d{dist}
{}

void ch14_e17::Distributor_controller::show()
{
	const Graph_lib::Shape& start = d.leftmost_element();
	const Graph_lib::Shape& end = d.rightmost_element();
	if (is_sentinel(start)) {
		return; // Presume empty
	}
	show_next(start, end);
}

void ch14_e17::Distributor_controller::hide()
{
	const Graph_lib::Shape& start = d.leftmost_element();
	const Graph_lib::Shape& end = d.rightmost_element();
	if (is_sentinel(start)) {
		return; // Presume empty
	}
	hide_next(start, end);
}

bool ch14_e17::Distributor_controller::is_visible() const
{
	return Distributor_controller::next_is_visible(d.leftmost_element(),
	                                               d.rightmost_element());
}

void ch14_e17::Distributor_controller::show_next(const Graph_lib::Shape& start,
                                                 const Graph_lib::Shape& end)
{
	if (is_sentinel(start)) {
		throw std::runtime_error("Distributor contains a sentinel shape");
	}
	d.show_element(start);
	if (&start != &end) {
		show_next(d.element_right_of(start), end);
	}
}

void ch14_e17::Distributor_controller::hide_next(const Graph_lib::Shape& start,
                                                 const Graph_lib::Shape& end)
{
	if (is_sentinel(start)) {
		throw std::runtime_error("Distributor contains a sentinel shape");
	}
	d.hide_element(start);
	if (&start != &end) {
		hide_next(d.element_right_of(start), end);
	}
}

bool ch14_e17::Distributor_controller::next_is_visible(
    const Graph_lib::Shape& start, const Graph_lib::Shape& end) const
{
	if (is_sentinel(start)) {
		throw std::runtime_error("Distributor contains a sentinel shape");
	}
	if (d.element_is_visible(start)) {
		if (&start == &end) {
			return true;
		} else {
			return Distributor_controller::next_is_visible(d.element_right_of(
			                                                   start),
			                                               end);
		}
	}
	return false;
}
