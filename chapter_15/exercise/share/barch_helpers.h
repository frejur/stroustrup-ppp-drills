#ifndef BARCH_HELPERS_H
#define BARCH_HELPERS_H

#include "../../lib/Graph.h"

namespace chart {
class Bar_chart; // Forward declare
}

namespace barch_hlp {

void add_name_value_pairs_from_file(chart::Bar_chart& bar_chart,
                                    const std::string& filename);

}
#endif // BARCH_HELPERS_H
