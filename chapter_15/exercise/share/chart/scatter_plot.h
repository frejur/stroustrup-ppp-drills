#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H
#include "chart.h"
#include "elem.h"

namespace chart {

class Scatter_plot : public Chart
{
public:
	Scatter_plot(Graph_lib::Point origin, int width, int height, int point_size);

protected:
};

} // namespace chart

#endif // SCATTER_PLOT_H
