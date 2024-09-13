#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "../../lib/Graph.h"
#include <algorithm>
#include <string>

namespace ch14_e11 {

namespace {
const Graph_lib::Font& label_font()
{
	static const Graph_lib::Font& f{Graph_lib::Font::screen};
	return f;
}
constexpr int default_node_height{10};
constexpr int default_minimum_node_padding{10};
} // namespace

class Circle_node : public Graph_lib::Ellipse
{
public:
	Circle_node(Graph_lib::Point position,
	            int height,
	            int font_size,
	            const std::string& label = "")
	    : Graph_lib::Ellipse(position,
	                         0.5
	                             * (std::max)(height,
	                                          calc_lb_width(label, font_size)),
	                         0.5 * height)
	    , fnt_sz(font_size)
	{
		set_color(Graph_lib::Color::black);
		set_fill_color(Graph_lib::Color::invisible);
	};
	virtual int point_is_on_node(Graph_lib::Point pt) { return -1; };
	void update_width()
	{
		set_major((std::max)(minor(), calc_lb_width(lb, fnt_sz)));
	};
	virtual void draw_lines() const;

protected:
private:
	std::string lb;
	const Graph_lib::Font fnt{label_font()};
	int fnt_sz;

	void set_minor(){}; // hide
	int calc_lb_width(const std::string& s, int font_size) const;
};

//------------------------------------------------------------------------------

class Binary_tree : public Graph_lib::Shape
{
public:
	Binary_tree(Graph_lib::Point root_position,
	            int level,
	            int node_height = default_node_height,
	            int min_node_padding = default_minimum_node_padding)
	    : lv(valid_level(level))
	    , num_nodes(std::pow(2, lv) - 1)
	    , node_h(valid_node_h(node_height))
	    , min_node_pad(valid_node_pad(min_node_padding))
	    , fnt(label_font())
	    , fnt_sz(calc_font_size(node_h))
	{
		add(root_position);
		add_nodes();
	};

	// Graph_lib::Point node_position(const std::string& address) const;
	virtual void move(int offset_x, int offset_y) override;
	virtual void draw_lines() const override;
	void move_sub_tree(const int parent, int offset_x, int offset_y);

private:
	int lv;
	int num_nodes;
	int node_h;
	int min_node_pad;
	const Graph_lib::Font fnt;
	int fnt_sz;
	Graph_lib::Vector_ref<Shape> nodes;

	void add_nodes();

	int parent_index(int index) const;
	int l_child_index(int index) const { return 2 * index + 1; };
	int r_child_index(int index) const { return 2 * index + 2; };
	int address_to_index(const std::string& address) const;
	int calc_font_size(int height) const;

	int node_level(int n) const;
	bool is_leaf_node(int n) const;
	bool index_is_valid(int i) const;

	// Validates values, will throw an exception if not valid
	int valid_index(int i) const;
	int valid_level(int l) const;
	int valid_node_h(int h) const;
	int valid_node_pad(int p) const;
};

} // namespace ch14_e11

#endif // BINARY_TREE_H
