#ifndef SHAPE_DISTRIBUTOR_H
#define SHAPE_DISTRIBUTOR_H
#include "../../lib/Graph.h"
#include "nodes.h"

namespace ch14_e17 {

class Shape_distributor;
class Sentinel_shape;

class detail
{
	friend Shape_distributor;
	static constexpr int min_angle{33};
	static constexpr int max_angle{170};
	static constexpr int default_angle{170};
	static constexpr int default_v_space{8};
};

enum class Alignment_side { Left, Right };

//------------------------------------------------------------------------------

class Sentinel_shape : private Graph_lib::Shape
{
public:
	using Graph_lib::Shape::Shape;
	Sentinel_shape(){};
	void draw() const {}; // Hide just in case
	const Graph_lib::Shape& as_shape() const { return *this; }
};

bool is_sentinel(const Graph_lib::Shape& s);

//------------------------------------------------------------------------------

class Shape_distributor
{
public:
	Shape_distributor(Graph_lib::Point origin,
	                  int spread_angle = detail::default_angle,
	                  int vertical_space = detail::default_v_space)
	    : angle(valid_angle(spread_angle))
	    , v_space(vertical_space)
	    , o(origin){};
	Graph_lib::Point origin() const { return o; };

	void distribute();
	void sort(bool reverse = false);

	Graph_lib::Point element_origin(const Graph_lib::Shape& s) const;
	int element_width(const Graph_lib::Shape& s) const;
	int element_height(const Graph_lib::Shape& s) const;

	void change_place(const Graph_lib::Shape& element_to_move,
	                  const Graph_lib::Shape& element_to_shift);
	void place_in_middle(const Graph_lib::Shape& element_to_move);

	void set_color(Graph_lib::Color color);
	void set_fill_color(Graph_lib::Color color);
	void set_color_of_element(Graph_lib::Color color,
	                          const Graph_lib::Shape& element);
	void set_fill_color_of_element(Graph_lib::Color color,
	                               const Graph_lib::Shape& element);
	bool element_is_visible(const Graph_lib::Shape& element) const;
	void hide_element(const Graph_lib::Shape& element);
	void show_element(const Graph_lib::Shape& element);

	void move(int offs_x, int offs_y);
	void move_element(int offs_x, int offs_y, const Graph_lib::Shape& shape);

	int number_of_elements() const { return shp.size(); };

	const Graph_lib::Shape& element_at_point(Graph_lib::Point point) const;
	const Graph_lib::Shape& leftmost_element() const;
	const Graph_lib::Shape& rightmost_element() const;
	const Graph_lib::Shape& element_below(const Graph_lib::Shape& element) const;
	const Graph_lib::Shape& element_left_of(
	    const Graph_lib::Shape& element) const;
	const Graph_lib::Shape& element_right_of(
	    const Graph_lib::Shape& element) const;

	static inline const Graph_lib::Shape& sentinel()
	{
		static const Sentinel_shape s{};
		return s.as_shape();
	};

	int vertical_space() const { return v_space; }
	int horizontal_space() const { return v_space; /* TODO */ }

protected:
	int valid_idx(int i) const;
	static constexpr int min_a = detail::min_angle;
	static constexpr int max_a = detail::max_angle;

	virtual int find_element_at_pt(Graph_lib::Point point) const = 0;
	virtual Graph_lib::Point shape_origin(int idx) const = 0;
	virtual int shape_width(int idx) const = 0;
	virtual int shape_height(int idx) const = 0;

	void add_shp(Graph_lib::Shape& s);
	const Graph_lib::Shape& get_shp(int idx) const;

	int find_element(const Graph_lib::Shape& s) const;
	int ordered_index(int idx) const;
	void move_shape(int offs_x, int offs_y, int index);

	bool in_middle(int ordered_index) const;
	bool at_far_left(int ordered_index) const;
	bool at_far_right(int ordered_index) const;

private:
	const float angle;
	const int v_space;
	Graph_lib::Point o;
	Graph_lib::Vector_ref<Graph_lib::Shape> shp;
	std::vector<int> shp_order; // Stores the order in which shapes are distributed

	void swap(int a_idx, int b_idx);
	void sort_by_w_asc();
	void sort_by_w_desc();

	float valid_angle(int a) const;
	int offset_to_align_with_angle(Alignment_side s);
};

//------------------------------------------------------------------------------

class Node_distributor : public Shape_distributor
{
public:
	using Shape_distributor::Shape_distributor;
	void add_node(Node& node)
	{
		if (!is_sentinel(node)) {
			add_shp(node);
		}
	};
	std::string node_label(const Graph_lib::Shape& node) const
	{
		return dynamic_cast<const Node&>(get_shp(find_element(node))).label();
	}

private:
	virtual Graph_lib::Point shape_origin(int idx) const override
	{
		return dynamic_cast<const BOX::Box&>(get_shp(idx)).bbox_origin();
	}
	virtual int shape_width(int idx) const override
	{
		return dynamic_cast<const BOX::Box&>(get_shp(idx)).width();
	}
	virtual int shape_height(int idx) const override
	{
		return dynamic_cast<const BOX::Box&>(get_shp(idx)).height();
	}

private:
	virtual int find_element_at_pt(Graph_lib::Point point) const override;
};

} // namespace ch14_e17

#endif // SHAPE_DISTRIBUTOR_H
