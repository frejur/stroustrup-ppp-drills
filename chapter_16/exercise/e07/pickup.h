#ifndef PICKUP_H
#define PICKUP_H
#include "../../lib/Graph.h"

class Pickup : public Graph_lib::Image
{
public:
	enum class Direction { NW = 0, N, NE, E, SE, S, SW, W };
	Pickup(Graph_lib::Point center, int size);
	Direction direction() const { return dir; };
	void set_direction(Direction d);

	int size() const { return spr_sz; }
	int bounding_box_size() const { return bbox_sz; }

	void set_bounding_box_size(int s) { bbox_sz = valid_bbox_sz(s); }

	Graph_lib::Point center() const
	{
		return {point(0).x + size() / 2, point(0).y + size() / 2};
	};

private:
	int spr_sz;
	int bbox_sz;
	Direction dir;
	void upd_spr_sheet(Direction d);

	int valid_sz(int sz) const;
	int valid_bbox_sz(int sz) const;
};

#endif
