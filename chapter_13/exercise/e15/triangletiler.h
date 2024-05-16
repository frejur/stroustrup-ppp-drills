#ifndef TRIANGLETILER_H
#define TRIANGLETILER_H

#include "../share/tiler/tiler.h"

namespace Tile_lib { //--------------------------------------------------------

class Triangle_tiler : public Tiler
{
public:
	Triangle_tiler(
	    Graph_lib::Point o, int w, int h, int tri_side, double rotation);
};

} // namespace Tile_lib -----------------------------------------------------------
#endif // TRIANGLETILER_H
