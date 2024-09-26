#ifndef FCT_H
#define FCT_H
#include "../../lib/Graph.h"

namespace fct {

using Fn = std::function<double(double)>;

struct Range
{
	double r1;
	double r2;
};

class Fct : public Graph_lib::Shape
{
public:
	Fct(Fn f,
	    double r1,
	    double r2,
	    Graph_lib::Point orig,
	    int count = 100,
	    double xscale = 25,
	    double yscale = 25);
	explicit Fct(double (*f)(double),
	             double r1,
	             double r2,
	             Graph_lib::Point orig,
	             int count = 100,
	             double xscale = 25,
	             double yscale = 25);

	void set_function(Fn f);
	;
	void set_function(double (*f)(double));
	;
	void set_range(int start, int end);
	;
	void set_origin(Graph_lib::Point o);
	;
	void set_count(int c);
	;
	void set_x_scale(double xscale);
	;
	void set_y_scale(double yscale);
	;

	virtual void draw_lines() const override;

private:
	Fn f_;
	Range r_;
	Graph_lib::Point xy_;
	int count_;
	double xscale_;
	double yscale_;

	void upd();

	// Invalid throws exception
	Range valid_range(double start, double end);
	int valid_count(int c);
};

} // namespace fct

#endif // FCT_H
