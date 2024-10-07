#ifndef CH15_HELPERS_H
#define CH15_HELPERS_H
#include "../../lib/Graph.h"

namespace barch {
class Bar_chart;
}

namespace ch15_hlp {

void add_name_value_pairs_from_file(barch::Bar_chart& bar_chart,
                                    const std::string& filename);

int calc_lb_w(const std::string& txt, Graph_lib::Font f, int f_sz);

}

#endif // CH15_HELPERS_H
