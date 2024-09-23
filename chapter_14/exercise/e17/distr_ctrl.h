#ifndef DISTR_CTRL_H
#define DISTR_CTRL_H
#include "shp_distr.h"

namespace ch14_e17 {

class Controller
{
public:
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual bool is_visible() const = 0;
};

// Controls the visibility of a Shape ------------------------------------------
class Shape_controller : public Controller
{
public:
	Shape_controller(Graph_lib::Shape& shape)
	    : s(shape){};
	virtual void show() override;
	virtual void hide() override;
	virtual bool is_visible() const override
	{
		return (s.color().visibility() || s.fill_color().visibility());
	};

private:
	Graph_lib::Shape& s;
};

// Controls the visibility of a Shape_distributor ------------------------------
class Distributor_controller : public Controller
{
public:
	Distributor_controller(Shape_distributor& dist);
	virtual void show() override;
	virtual void hide() override;
	virtual bool is_visible() const override;

private:
	Shape_distributor& d;
	void show_next(const Graph_lib::Shape& s, const Graph_lib::Shape& e);
	void hide_next(const Graph_lib::Shape& s, const Graph_lib::Shape& e);
	bool next_is_visible(const Graph_lib::Shape& s,
	                     const Graph_lib::Shape& e) const;
};

} // namespace ch14_e17

#endif // DISTR_CTRL_H
